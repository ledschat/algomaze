
#include "redAgent.h"

#include "mazeAlgorithm.h"

#include "matlab/generateMaze_emxAPI.h"
#include "matlab/generateMaze_emxutil.h"
#include "matlab/updateStartPosition.h"

#define NS LedsChat::RedAgent

NS::RedAgent(Maze & maze, const StartData & data)
	: m_currentSolution(0), m_cpt(0)
	  
{
	setMaze(maze, data);
}

void NS::setMaze(Maze & maze, const StartData & data)
{
	m_maze = &maze;
	m_start = data.position;
	m_baseDirection = data.direction;

	m_solution = Solution(m_maze->gridSize(), std::vector<bool>(m_maze->gridSize()));

	struct0_T copy;
	emxInit_struct0_T(&copy);

	emxCopyStruct_struct0_T(&copy, &m_maze->grid());
	updateStartPosition(&copy, m_start.x + 1, m_start.y + 1);		
	TremauxAlgorithm algo;
	algo.init();

	while(!algo.update(copy));

	for(unsigned j = 0; j < m_maze->gridSize() ; j++)
	{
		for(unsigned i = 0 ;i < m_maze->gridSize(); i++)
		{
			double val = copy.grid->data[i + j * m_maze->gridSize()];
			if(val == m_maze->grid().GoodPath || val == m_maze->grid().StartColor || val == m_maze->grid().CurrentPos || val == m_maze->grid().fadingColorMapEnd)
				m_solution[j][i] = true;
			else
				m_solution[j][i] = false;
		}
	}

	algo.terminate();
	emxDestroy_struct0_T(copy);
	
	reset();
}

void NS::update()
{
	if(m_cpt > 2)
	{
		m_state = move();
		m_currentSolution = m_currentSolution <= 0.05f ? 0.f : m_currentSolution - 0.01f;

		if(m_drawing.front().second == 0)
			m_drawing.pop_front();

		auto end = --m_drawing.end();
		for(auto it = m_drawing.begin(); it != end; ++it) 
			it->second = it->second <= 0.05f ? 0.f : it->second - 0.01f;

		if(m_drawing.back().first == m_position) return;

		m_drawing.push_back(std::make_pair(m_position, 1.f));		

		m_cpt = 0;
	}
	else
		++m_cpt;
}	

void NS::draw(RenderWall & wall)
{
	for(auto el : m_drawing)
	{
		wall[el.first.y][el.first.x].r         = static_cast<uint8_t>(255 * el.second);
		wall[el.first.y + 1][el.first.x].r     = static_cast<uint8_t>(255 * el.second);
		wall[el.first.y + 1][el.first.x + 1].r = static_cast<uint8_t>(255 * el.second);
		wall[el.first.y][el.first.x + 1].r     = static_cast<uint8_t>(255 * el.second);
	}

	if(m_currentSolution > 0)
	{
		for(unsigned j = 0; j < m_maze->gridSize() ; j++)
		{
			for(unsigned i = 0 ;i < m_maze->gridSize(); i++)
			{
				if(m_solution[j][i])
					wall[j][i].r = static_cast<uint8_t>(255 * m_currentSolution);
				
			}

		}
	}
}


LedsChat::AgentState NS::move()
{
	if(m_state == AgentStopped) return AgentStopped;

	if(m_position.x == 0 || m_position.x == (int) m_maze->gridSize() - 2 || m_position.y == 0 || m_position.y == (int) m_maze->gridSize() - 2) return AgentOut;

	std::vector<uint8_t> directions;
	m_maze->listDirections(m_position, directions);


	if(m_currentDirection != Directions::noDirection)
	{
		if(m_leftIntersection)
		{
			m_leftIntersection = false;
			m_oldInstructions = directions;
			m_position = m_position + Directions::move[m_currentDirection];

			return AgentRunning;
		}

		if(m_oldInstructions.size() == directions.size())
		{
			bool different = false;
			for(unsigned i(0); i < directions.size(); ++i)
				if(m_oldInstructions[i] != directions[i]) different = true;

			if(!different)
			{
				m_position = m_position + Directions::move[m_currentDirection];
				return AgentRunning;
			}
		}
	}

	m_oldInstructions = directions;

	if(!setDirection())
	{
		m_blockedReason = "noDirection";
		return AgentStopped;
	}

	bool canGo = false;

	for(unsigned i(0); i < directions.size(); ++i)
		if(m_currentDirection == directions[i]) canGo = true;

	if(canGo)
	{
		m_position = m_position + Directions::move[m_currentDirection];
		return AgentRunning;
	}

	m_blockedReason = "wall";
	return AgentStopped;


}

void NS::printSolution()
{
	m_currentSolution = 1;
}

bool NS::setDirection()
{
	if(m_instructions.size() == 0) return false;

	int8_t dir = m_instructions.front();
	m_instructions.pop();

	if(dir == -1)
		m_currentDirection = m_currentDirection == 0 ? 3 : m_currentDirection - 1;
	else if(dir == 1)
		m_currentDirection = m_currentDirection == 3 ? 0 : m_currentDirection + 1;

	m_leftIntersection = true;

	return true;
}

unsigned NS::getNbInstructions()
{
	return static_cast<unsigned>(m_instructions.size());
}

void NS::addInstruction(int8_t direction)
{
	m_instructions.push(direction);
}

std::string NS::getBlockedReason()
{
	return m_blockedReason;
}

void NS::reset()
{
	std::queue<int8_t> empty;
	std::swap( m_instructions, empty );

	m_currentDirection = m_baseDirection;
	m_position = m_start;
	m_state = AgentStopped;
	m_leftIntersection = false;

	addInstruction(0);

	m_maze->listDirections(m_position, m_oldInstructions);

	m_drawing.clear();
	m_drawing.push_back(std::make_pair(m_position, 1.f));
}

void NS::start()
{
	m_state = AgentRunning;
}

LedsChat::AgentState NS::getState() const
{
	return m_state;
}

#undef NS
