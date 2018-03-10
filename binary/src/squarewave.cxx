
#include "squarewave.h"
#include "title.h"

#define NS LedsChat::Squarewave

NS::Squarewave(unsigned size)
    : m_size(size)
{
    m_matrix.resize(size * size);

    reset();

}
void NS::reset()
{
    // initialize flow and qte
    for(unsigned i(0); i < m_size * m_size; i = i+1)
    {
      
        for(unsigned j(0); j < 4; j = j+1)
        {

            m_matrix[i].flow[j] = 0.0;

            if(getNeighbour(i, j) == -1)
                m_matrix[i].canFlow[j] = 0;
            else
                m_matrix[i].canFlow[j] = 1;
        }

        m_matrix[i].qte = 0.0;
        m_matrix[i].localFlow = 0.0;
    }
    
    m_matrix[(m_size * m_size + m_size) / 2].qte = 1000;
    m_currentLetter = 0;
    m_cpt = 0;
}

void NS::update()
{
    // update flows and quantities
    for(unsigned i(0); i < m_size * m_size; ++i)
    {

        float myqte = m_matrix[i].qte;
        float newqte = myqte; // updated quantitiy
        float newlocalFlow = m_matrix[i].localFlow;

        if(newlocalFlow > 0)
        {
            newlocalFlow = newlocalFlow * paramPreservationgreenical - 
                           myqte * paramSpringgreenical - 
                           newlocalFlow * newlocalFlow * paramFrictiongreenical;
        }
        else
        {
            newlocalFlow = newlocalFlow * paramPreservationgreenical - 
                           myqte * paramSpringgreenical + 
                           newlocalFlow * newlocalFlow * paramFrictiongreenical;       
        }

       
        m_matrix[i].localFlow = newlocalFlow;
        newqte += newlocalFlow;
         
        for(unsigned j(0); j < 4; ++j)
        {

            if(m_matrix[i].canFlow[j])
            {
                  
                float oldflow = m_matrix[i].flow[j];   
                float delta = (m_matrix[getNeighbour(i, j)].qte - myqte); // inflow increase from neighbor
                float newflow;

                if(oldflow > 0)
                {
                    newflow = oldflow * paramPreservationTransfer + 
                              delta * paramAccellerationTransfer - 
                              oldflow * oldflow * paramFrictionTransfer;
                }
                else 
                {
                    newflow = oldflow * paramPreservationTransfer + 
                              delta * paramAccellerationTransfer + 
                              oldflow * oldflow * paramFrictionTransfer;
                }

                m_matrix[i].flow[j] = newflow;
                newqte += newflow;
            }
        }
          
        m_matrix[i].change = newqte - m_matrix[i].qte;
        m_matrix[i].qte = newqte;
    }

    m_offset = (m_offset + 1) % 360;

    if(m_currentLetter == imgLettersSize)
    {
        if(m_cpt == 400)
        {
            m_currentLetter = 0;
            m_cpt = 0;
        }
        else
            ++m_cpt;
    }
    else
    {
        if((int)m_cpt >= 5 + std::rand() % 10)
        {
            ++m_currentLetter;
            m_cpt = 0;
        }
        else
            ++m_cpt;

    }
    
}

void NS::draw(RenderWall & wall)
{

    for(unsigned i(0); i < m_size * m_size; ++i) 
    {

        float fqte = 20.0f * m_matrix[i].change;
        
        if(fqte >= 0.0)
        {

            if(!m_matrix[i].oldSign) 
                m_matrix[i].myHue = m_offset;

            printHSV(i, m_matrix[i].myHue, 360, discretize(fqte), wall);

            m_matrix[i].oldSign = 1;
        } 
        else
        {
      
            if(m_matrix[i].oldSign) 
                m_matrix[i].myHue = m_offset + 180 % 360;

            printHSV(i, m_matrix[i].myHue, 360, discretize(-fqte), wall);
           
            m_matrix[i].oldSign = 0;

        }
    }

    Vector base(0, 20);

    for(unsigned i(0); i < m_currentLetter; ++i)
    {
        for(unsigned j(0); j < imgLetters[i].h; ++j)
        {
            for(unsigned k(0); k < imgLetters[i].w; ++k)
            {
                uint32_t x = k + imgLetters[i].x;
                uint32_t y = j + imgLetters[i].y;
                if(imgData[y * imgWidth + x])
                {
                    wall[y + base.y][x + base.x] = RenderWall::Color(255, 255, 255);
                }
                
            }
        }
    }
}

int NS::getNeighbour(unsigned id, unsigned direction)
{
    switch(direction)
    {
        case 0:
            if(id / m_size == 0) return -1;
            return id - m_size;
        case 1:
            if(id % m_size == m_size - 1) return -1;
            return id + 1;
        case 2:
            if(id / m_size == m_size - 1) return -1;
            return id + m_size;
        case 3:
            if(id % m_size == 0) return 0;
            return id - 1;
    }

    return -1;
}


int NS::discretize(float in)
{
    int result = static_cast<int>(in / 2.0);
    if(result < 0) result = 0;
    if(result > 255) result = 255;

    return result;
}

void NS::printHSV(int i, int value, int max, int colormax, RenderWall & wall)
{

    int red, green, blue;
    
    int intervalSize = max / 6;
    int rank  = (value % max) / intervalSize;
    int remain = (value % max) - rank * intervalSize;
    
    if(rank == 0)
    {
        red = colormax;
        blue = 0;
        green = remain * colormax / intervalSize;
    }
    else if(rank == 1)
    {
        red = colormax - (remain * colormax / intervalSize);
        blue = 0;
        green = colormax;
    }
    else if(rank == 2)
    {
        red = 0;
        blue = remain * colormax / intervalSize;
        green = colormax;
    }
    else if(rank == 3)
    {
        red = 0;
        blue = colormax;
        green = colormax - (remain * colormax / intervalSize);
    }
    else if(rank == 4)
    {
        red = remain * colormax / intervalSize;
        blue = colormax;
        green = 0;
    }
    else 
    {
        red = colormax;
        blue = colormax - (remain * colormax / intervalSize);
        green = 0;
    }

    unsigned x = i % m_size;
    unsigned y = i / m_size;

    wall[y][x].r = red;
    wall[y][x].g = green;
    wall[y][x].b = blue;
    
}

#undef NS