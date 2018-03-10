
#ifndef LEDSCHAT_GAME_H_
#define LEDSCHAT_GAME_H_

#include "ledschat-1.0.h"

#include "maze.h"
#include "redAgent.h"
#include "blueAgent.h"
#include "greenAgent.h"
#include "squarewave.h"
#include "mazeList.h"

#include <memory>

namespace LedsChat
{
    class Game
    {
        public:

            Game (RenderWall & wall, uint32_t size);

            void run ();

        private:
            using MazePtr = std::unique_ptr<Maze>;

            MazeList     m_mazeList;
            MazeData     m_currentData;  

            MazePtr      m_maze;
            RenderWall & m_wall;
            Squarewave   m_squarewave;

            RedAgent     m_redAgent;
            GreenAgent   m_greenAgent;
            BlueAgent    m_blueAgent;

            
    };

    
}

#endif
