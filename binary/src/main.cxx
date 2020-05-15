

#include "ledschat.h"
#include "game.h"

#ifdef _WIN32
#pragma comment(lib, "Ws2_32.lib")
#endif

int main()
{
	LedsChat::RenderWall wall;

	if(!wall.connect()) { std::cerr << "no response" << std::endl; return 1; } 

	
	LedsChat::Game game(wall, 80);

	game.run();

	return 0;
}
