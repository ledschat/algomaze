
#include "game.h"

#include "matlab/eml_rand_mt19937ar_stateful.h"

#include <fstream>

#define NS LedsChat::Game

NS::Game(RenderWall & wall, uint32_t size)
	: m_currentData(m_mazeList.getRandomMaze()), m_maze(std::make_unique<Maze>(m_currentData)), 
	  m_wall(wall), m_squarewave(size), 
	  m_redAgent(*m_maze, m_currentData.redAgent), m_greenAgent(*m_maze, m_currentData.greenAgent), m_blueAgent(*m_maze, m_currentData.blueAgent)
{
	rt_InitInfAndNaN(8U);
    startPos_not_empty_init();
    curPos_not_empty_init();
    c_eml_rand_mt19937ar_stateful_i();
}

void NS::run()
{

	m_wall.setFramerate(50);

    bool puppetOrders = false;
    bool followingOrders = false;

    bool screenSaver = false;

    unsigned cptScreenSaver = 0;

    unsigned cptUp = 0;

    std::ifstream settings("data/settings.json");

   	LedsChat::Json settingsJson;
   	settings >> settingsJson;

   	unsigned screenSaverTiming = settingsJson["screensaver"];

   	m_blueAgent.setLuminosity(settingsJson["blueLuminosity"]);

	while(m_wall.isRunning())
	{				


		LedsChat::Json json;
		while(m_wall.newData(json))
		{
			if(json["cmd"] == "alive")
			{
				cptScreenSaver = 0;
			}
			else if(json["cmd"] == "pathPuppetAgent")
			{
				cptUp = 400;
			}

			else if(json["cmd"] == "movePuppetAgent")
			{
				puppetOrders = true;
				for (auto& el : json["orders"])
					m_redAgent.addInstruction(el);
				m_redAgent.start();
			}

			else if(json["cmd"] == "moveFollowingAgent")
			{

				followingOrders = true;

				for (auto& el : json["algorithm"])
				{
					int direction = el["direction"];

					m_greenAgent.addAlgorithmStep(LedsChat::AlgorithmStep(el["state"][0], el["state"][1], el["state"][2], direction));
				}

				m_greenAgent.start();
			}

			else if(json["cmd"] == "restartPuppetAgent")
			{
				puppetOrders = false;
				m_redAgent.reset();
			}

			else if(json["cmd"] == "restartFollowingAgent")
			{
				followingOrders = false;
				m_greenAgent.reset();
			}
		}

		if(m_blueAgent.serial())
			cptScreenSaver = 0;

		if(cptScreenSaver == 0 && screenSaver)
		{
			screenSaver = false;
			// TODO change maze
			m_currentData = m_mazeList.getRandomMaze(); 
			m_maze = std::make_unique<Maze>(m_currentData); 
			m_redAgent.setMaze(*m_maze, m_currentData.redAgent);
			m_greenAgent.setMaze(*m_maze, m_currentData.greenAgent);
			m_blueAgent.setMaze(*m_maze, m_currentData.blueAgent);
		}

		if(cptScreenSaver < screenSaverTiming * 50)
			cptScreenSaver++;
		else if(!screenSaver)
		{
			screenSaver = true;
			m_squarewave.reset();
			m_blueAgent.stop();
		}
		

		if(screenSaver)
		{
			m_squarewave.update();
			m_squarewave.draw(m_wall);

		}
		else
		{
		
			if(cptUp > 0)
			{
				m_redAgent.printSolution();
				--cptUp;
			}

			

			m_redAgent.update();
			m_greenAgent.update();	

			if(m_blueAgent.update())
				cptScreenSaver = 0;
			
			if(puppetOrders)
			{
				switch(m_redAgent.getState())
				{
					case AgentRunning:
						m_wall.send({{"cmd", "puppetRemaining"}, {"remaining", m_redAgent.getNbInstructions()}});
						break;
					case AgentStopped:
						puppetOrders = false;
						m_wall.send({{"cmd", "puppetKO"}, {"reason", m_redAgent.getBlockedReason()}});
						break;
					case AgentOut:
						puppetOrders = false;
						m_wall.send({{"cmd", "puppetOK"}});
						break;

				}
			}



			if(followingOrders)
			{
				switch(m_greenAgent.getState())
				{
					case AgentRunning:
						break;
					case AgentStopped:
						followingOrders = false;
						m_wall.send({{"cmd", "followingKO"}, {"reason", m_greenAgent.getBlockedReason()}});
						break;
					case AgentOut:
						followingOrders = false;
						m_wall.send({{"cmd", "followingOK"}});
						break;

				}
			}



			m_maze->draw(m_wall);
			m_blueAgent.draw(m_wall);
			m_greenAgent.draw(m_wall);
			m_redAgent.draw(m_wall);
		}
		
		m_wall.update();
	}
}

#undef NS
