
#include "maze.h"

#include "matlab/generateMaze_emxAPI.h"
#include "matlab/generateMaze_emxutil.h"

#define NS LedsChat::Maze

NS::Maze(uint32_t gridSize)
	: m_gridSize(gridSize), m_cpt(0)			  
{
	
	// Initialize the application.
	emxInit_struct0_T(&m_grid);
	// Invoke the entry-point functions.
	generateMaze(gridSize, &m_grid);


	for(unsigned j (0); j < m_gridSize; ++j)
	{
		for(unsigned i (0); i < m_gridSize; ++i)
		{				
			char color = static_cast<char>(m_grid.grid->data[j * m_gridSize + i]);

			std::cout << (color == m_grid.Wall ? '1' : '0');

		}

		std::cout << '\n';
	}

	std::cout << std::endl;
}

NS::Maze(const MazeData & data)
	: m_gridSize(data.size)				  
{
	
	// Initialize the application.
	emxInit_struct0_T(&m_grid);
	// Invoke the entry-point functions.
	generateMaze(m_gridSize, &m_grid, data.seed);//data.seed);

	emxInit_struct0_T(&m_copy);
	emxCopyStruct_struct0_T(&m_copy, &m_grid);

}

NS::~Maze()
{
	// Terminate the application.
    emxDestroy_struct0_T(m_grid);
}

void NS::draw(RenderWall & wall)
{
	for(unsigned j (0); j < m_gridSize; ++j)
	{
		for(unsigned i (0); i < m_gridSize; ++i)
		{				
			char color = static_cast<char>(m_grid.grid->data[j * m_gridSize + i]);

			if(color == m_grid.Wall)
				wall[j][i] = RenderWall::Color(255, 255, 255);
			else
				wall[j][i] = RenderWall::Color(0, 0, 0);
		}
	}

	Vector exit[2];
	exit[0].x = ((int)m_grid.exit[0] - 1) % (int)(m_grid.numCols);
	exit[0].y = ((int)m_grid.exit[0] - 1) / (int)(m_grid.numCols);
	exit[1].x = ((int)m_grid.exit[1] - 1) % (int)(m_grid.numCols);
	exit[1].y = ((int)m_grid.exit[1] - 1) / (int)(m_grid.numCols);

	Vector colors[2];

	if(exit[0].x == exit[1].x)
	{
		colors[0].x = exit[0].x;
		colors[0].y = exit[0].y - 1;
		colors[1].x = exit[0].x;
		colors[1].y = exit[1].y + 1;
	}
	else
	{
		colors[0].x = exit[0].x - 1;
		colors[0].y = exit[0].y;
		colors[1].x = exit[1].x + 1;
		colors[1].y = exit[0].y;
	}
	

	for(unsigned i(0); i < 2; ++i)
	{
		unsigned color = m_cpt > 100 ? (200 - m_cpt) : m_cpt;
		wall[exit[i].y][exit[i].x] = RenderWall::Color(color, color, color);
	}

	for(unsigned i(0); i < 2; ++i)
	{
		wall[colors[i].y][colors[i].x] = RenderWall::Color(255, 150, 50);
	}


	m_cpt = (m_cpt + 3) % 200;
	
}


void NS::listDirections(const Vector & position, std::vector<uint8_t> & directions)
{
	for(unsigned i(0); i < 4; ++i)
	{
		Vector new1 = position + Directions::positions[i][0];
		Vector new2 = position + Directions::positions[i][1];

		char color1 = static_cast<char>(m_grid.grid->data[new1.y * m_gridSize + new1.x]);
		char color2 = static_cast<char>(m_grid.grid->data[new2.y * m_gridSize + new2.x]);

		if(color1 != m_grid.Wall && color2 != m_grid.Wall)
		{
			directions.push_back(i);
		}
	}
}

uint32_t NS::gridSize() const
{
	return m_gridSize;
}

struct0_T & NS::grid()
{
	return m_grid;
} 


void NS::reset()
{
	emxCopyStruct_struct0_T(&m_grid, &m_copy);
}

#undef NS
