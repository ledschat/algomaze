
#ifndef LEDSCHAT_BLUE_AGENT_H_
#define LEDSCHAT_BLUE_AGENT_H_

#include "utils.h"
#include "maze.h"
#include "mazeAlgorithm.h"
#include "mazeList.h"

#include <list>
#include <memory>
#include <chrono>
#include <fstream>

namespace LedsChat
{

	class BlueAgent
	{
		public:
			 BlueAgent (Maze & maze, const StartData & data);
			~BlueAgent ();

			void setMaze (Maze & maze, const StartData & data);
			bool update  ();
			void draw    (RenderWall & wall);			
			void start   ();
			void stop    ();
			void reset   ();
			void reset   (unsigned nextAlgorithm);

			void setLuminosity(float lum);

			bool serial  ();

		private:

			using Algos   = std::vector<std::unique_ptr<MazeAlgorithm>>;

			using Timepoint = std::chrono::time_point<std::chrono::system_clock>;
			using Micros = std::chrono::microseconds;

			std::vector<float> m_path;
			std::vector<std::string> m_tty;

			std::thread m_serialData;

			Maze *  m_maze;
			Algos   m_algos;
			bool    m_running;

			Vector  m_startPosition;

			int     m_serialFd;
			bool    m_serialOpened;

			unsigned m_usedMemory;
			unsigned m_time;

			char     m_tmp[7];
			unsigned m_currentTmp;

			bool     m_newData;

			unsigned m_errors;

			unsigned m_currentAlgorithm;
			bool     m_previousState;

			Timepoint       m_lastUpdate;
			Micros          m_micros;    

			unsigned        m_received;

			unsigned        m_waitStart;

			float           m_luminosity;

	};

}

#endif
