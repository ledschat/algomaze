
#ifndef LEDSCHAT_MAZE_LIST_H_
#define LEDSCHAT_MAZE_LIST_H_

#include "ledschat.h"
#include "utils.h"

namespace LedsChat
{
    struct StartData
    {
        Vector   position;
        uint32_t direction;
    };

    struct MazeData
    {
        uint32_t    size;

        uint32_t     seed;

        StartData   redAgent;
        StartData   greenAgent;
        StartData   blueAgent; 
    };

    class MazeList
    {
        public:

            MazeList();

            const MazeData & getRandomMaze() const;

        private:

            std::vector<MazeData> m_mazes;

    };

    
}

#endif
