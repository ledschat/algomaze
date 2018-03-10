

#include "ledschat-1.0.h"
#include "game.h"

int main()
{
	LedsChat::RenderWall wall;

	if(!wall.connect()) { std::cerr << "no response" << std::endl; return 1; } 

	
	LedsChat::Game game(wall, 80);

	game.run();

	return 0;
}
