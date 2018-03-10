
#ifndef LEDSCHAT_RED_AGENT_H_
#define LEDSCHAT_RED_AGENT_H_

#include "utils.h"
#include "maze.h"
#include "mazeList.h"

#include <list>
#include <vector>
#include <queue>

namespace LedsChat
{
    class RedAgent
    {
        public:
            RedAgent (Maze & maze, const StartData & data);

            void        setMaze           (Maze & maze, const StartData & data);
            void        update            ();
            void        draw              (RenderWall & wall);
            AgentState  move              ();
            void        printSolution     ();
            bool        setDirection      ();
            unsigned    getNbInstructions ();
            void        addInstruction    (int8_t direction);
            std::string getBlockedReason  ();
            void        reset             ();
            void        start             ();
            AgentState  getState          () const;

        private:
            using Solution = std::vector<std::vector<bool>>;
            using Drawing  = std::list<std::pair<Vector, float>>;

            Maze               * m_maze;
            Vector               m_start;
            Vector               m_position;
            std::queue<int8_t>   m_instructions;
            std::vector<uint8_t> m_oldInstructions;
            AgentState           m_state;
            std::string          m_blockedReason;
            bool                 m_leftIntersection;
            uint32_t             m_currentDirection;
            Solution             m_solution;
            Drawing              m_drawing;
            float                m_currentSolution;  
            uint32_t             m_baseDirection;     

            uint32_t             m_cpt;      
    };
    
}

#endif
