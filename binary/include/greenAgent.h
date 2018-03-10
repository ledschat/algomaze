
#ifndef LEDSCHAT_GREEN_AGENT_H_
#define LEDSCHAT_GREEN_AGENT_H_

#include "utils.h"
#include "maze.h"
#include "mazeList.h"

#include <list>
#include <vector>

namespace LedsChat
{
	struct AlgorithmStep
	{
		enum State
		{
			EmptyState = 0,
			FullState = 1,
			EmptyFullState = 2
		};

		AlgorithmStep(State forward, State left, State right, int8_t dir);

		State  state [3];
		int8_t direction;
	};

	class GreenAgent
	{
		public:
			GreenAgent (Maze & maze, const StartData & data);

			void        setMaze          (Maze & maze, const StartData & data);
			void        update           ();
			void        draw             (RenderWall & wall);
			AgentState  move             ();
			std::string getBlockedReason ();
			void        addAlgorithmStep (const AlgorithmStep & step);
			void        start            ();
			void        reset            ();
			AgentState  getState         () const;

		private:

			using UsedPaths = std::vector<std::vector<std::array<bool, 4>>>;
			using Drawing   = std::list<std::pair<Vector, float>>;

			Maze 					  * m_maze;	

			std::vector<AlgorithmStep>  m_algorithm;
			Vector 				 		m_start;
			Vector               		m_position;
			AgentState 			 	   	m_state;
			uint32_t 			 		m_currentDirection;
			std::string 				m_stoppedReason;
			UsedPaths                   m_usedPaths;
			Drawing                     m_drawing;
			uint32_t                    m_baseDirection;  
	};
	
}

#endif
