
#include "mazeList.h"

#define NS LedsChat::MazeList

NS::MazeList()
{
	std::string configFile = Fs::join(AppInfos::getAppDir(), "data/mazes.json");
    std::ifstream settings(configFile);

   	Json mazes;
   	settings >> mazes;

	for(auto & el: mazes)
	{
		MazeData maze;

		maze.size = el["size"];
		maze.seed = el["seed"];	

		maze.redAgent.position.x  = el["red"]["x"];
		maze.redAgent.position.y  = el["red"]["y"];
		maze.redAgent.direction   = Directions::stringToDirection(el["red"]["direction"]);

		maze.greenAgent.position.x  = el["green"]["x"];
		maze.greenAgent.position.y  = el["green"]["y"];
		maze.greenAgent.direction   = Directions::stringToDirection(el["green"]["direction"]);

		maze.blueAgent.position.x  = el["blue"]["x"];
		maze.blueAgent.position.y  = el["blue"]["y"];
		maze.blueAgent.direction   = Directions::stringToDirection(el["blue"]["direction"]);

		m_mazes.push_back(maze);

	}
}

const LedsChat::MazeData & NS::getRandomMaze() const
{
	return m_mazes[time(NULL) % m_mazes.size()];
}


#undef NS
