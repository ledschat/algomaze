
#include "greenAgent.h"

#define NS LedsChat::AlgorithmStep

NS::AlgorithmStep(State forward, State left, State right, int8_t dir)
{
	state[0] = forward;
	state[1] = left;
	state[2] = right;
	direction = dir;
}

#undef NS

#define NS LedsChat::GreenAgent

NS::GreenAgent(Maze & maze, const StartData & data)
	: m_start (1, 73)	 
{
	setMaze(maze, data);
}

void NS::setMaze(Maze & maze, const StartData & data)
{
	m_maze = &maze;
	m_start = data.position;
	m_baseDirection = data.direction;

	m_usedPaths = UsedPaths (maze.gridSize(), std::vector<std::array<bool, 4>>(maze.gridSize()));

	reset();
}

void NS::update()
{
	m_state = move();

	if(m_drawing.front().second == 0)
		m_drawing.pop_front();

	auto end = --m_drawing.end();
	for(auto it = m_drawing.begin(); it != end; ++it) 
		it->second = it->second <= 0.05f ? 0.f : it->second - 0.01f;

	if(m_drawing.back().first == m_position) return;

	m_drawing.push_back(std::make_pair(m_position, 1.f));		
}	

void NS::draw(RenderWall & wall)
{
	for(auto el : m_drawing)
	{
		wall[el.first.y][el.first.x].g         = static_cast<uint8_t>(255 * el.second);
		wall[el.first.y + 1][el.first.x].g     = static_cast<uint8_t>(255 * el.second);
		wall[el.first.y + 1][el.first.x + 1].g = static_cast<uint8_t>(255 * el.second);
		wall[el.first.y][el.first.x + 1].g     = static_cast<uint8_t>(255 * el.second);
	}
}	


LedsChat::AgentState NS::move()
{
	if(m_state == AgentStopped) return AgentStopped;

	if(m_position.x == 0 || m_position.x == (int) m_maze->gridSize() - 2 || m_position.y == 0 || m_position.y == (int) m_maze->gridSize() - 2) return AgentOut;

	std::vector<uint8_t> directions;
	m_maze->listDirections(m_position, directions);

	int8_t modif[] = {0, -1, 1};

	uint8_t newDirection = Directions::noDirection;

	for(auto & step : m_algorithm)
	{
		bool compatible = true;

		int8_t tmpDir = (step.direction + m_currentDirection + 4) % 4;

		for(unsigned i(0); i < 3; ++i)
		{
			if(step.state[i] == AlgorithmStep::EmptyFullState) continue;

			uint8_t dir = (modif[i] + m_currentDirection + 4) % 4;

			bool isPath = false;
			

			for(auto & d : directions)
				if(dir == d) isPath = true;


			if((isPath && step.state[i] == AlgorithmStep::FullState) || (!isPath && step.state[i] == AlgorithmStep::EmptyState))
			{
				compatible = false;
				break;
			}
		}

		if(compatible)
		{
			bool canGo = false;
			for(auto & d : directions)
			{
				if(tmpDir == d) canGo = true;
			}
			
			if(!canGo)
			{
				m_stoppedReason = "invalidRule";
				return AgentStopped;
			}

			newDirection = tmpDir;
			break;
		}
	}

	if(newDirection == Directions::noDirection)
	{
		m_stoppedReason = "noRule";
		return AgentStopped;
	}

	m_currentDirection = newDirection;
	m_position += Directions::move[m_currentDirection];


	if(m_usedPaths[m_position.y][m_position.x][m_currentDirection])
	{
		m_stoppedReason = "loop";
		return AgentStopped;
	}

	m_usedPaths[m_position.y][m_position.x][m_currentDirection] = true;

	return AgentRunning;

}

std::string NS::getBlockedReason()
{
	return m_stoppedReason;
}

void NS::addAlgorithmStep(const AlgorithmStep & step)
{
	m_algorithm.push_back(step);
}

void NS::start()
{
	m_state = AgentRunning;
}


void NS::reset()
{
	m_algorithm.clear();
	m_currentDirection = m_baseDirection;
	m_position = m_start;
	m_state = AgentStopped;

	m_drawing.clear();
	m_drawing.push_back(std::make_pair(m_position, 1.f));

	for(auto & l : m_usedPaths)
		for(auto & c : l)
			c.fill(false);
}


LedsChat::AgentState NS::getState() const
{
	return m_state;
}

#undef NS
