
#ifndef LEDSCHAT_MAZE_H_
#define LEDSCHAT_MAZE_H_

#include "ledschat.h"

#include "utils.h"
#include "mazeList.h"

#include "matlab/generateMaze.h"

namespace LedsChat
{
    class Maze
    {
        public:
             Maze (const MazeData & data);
             Maze (uint32_t gridSize);
            ~Maze ();

            void        draw           (RenderWall & wall);
            void        listDirections (const Vector & position, std::vector<uint8_t> & directions);
            uint32_t    gridSize       () const;
            struct0_T & grid           ();

            void        reset          ();


        private:
            uint32_t                    m_gridSize;
            struct0_T                   m_grid;
            struct0_T                   m_copy;

            unsigned                    m_cpt;

    };
    
}

#endif
