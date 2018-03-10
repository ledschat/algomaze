

#ifndef LEDSCHAT_MAZE_ALGORITHM_H__
#define LEDSCHAT_MAZE_ALGORITHM_H__

#include "matlab/updateMazeTremauxs.h"
#include "matlab/updateMazeWallFollower.h"
#include "matlab/updateMazePledge.h"
#include "matlab/updateMazeShortestPathBFS.h"
#include "matlab/updateMazeRandomMouse.h"

#include "utils.h"

#include <list>

namespace LedsChat
{

	struct MazeAlgorithm
	{
		virtual bool update(struct0_T & grid) = 0;
		virtual void init() = 0;
		virtual void terminate() = 0;
		virtual unsigned size() = 0;
		virtual unsigned memoryUsage() = 0;
	};

	struct TremauxAlgorithm : public MazeAlgorithm
	{
		virtual bool update(struct0_T & grid)
		{
			return updateMazeTremauxs(&grid) != 0;
		}

		virtual void init()
		{
			updateMazeTremauxs_init();
			curPos_not_empty_init();
		}

		virtual void terminate()
		{
			updateMazeTremauxs_free();
		}

		virtual unsigned size()
		{
			return 2;
		}

		virtual unsigned memoryUsage()
		{
			return getMazeTremauxsSize();
		}
	};

	struct RandomMouseAlgorithm : public MazeAlgorithm
	{
		virtual bool update(struct0_T & grid)
		{
			return updateMazeRandomMouse(&grid) != 0;
		}

		virtual void init()
		{
			updateMazeRandomMouse_init();
		}

		virtual void terminate()
		{
			updateMazeRandomMouse_free();
		}

		virtual unsigned size()
		{
			return 2;
		}

		virtual unsigned memoryUsage()
		{
			return 0;
		}
	};

	struct WallFollowerAlgorithm : public MazeAlgorithm
	{
		virtual bool update(struct0_T & grid)
		{
			return updateMazeWallFollower(&grid) != 0;
		}

		virtual void init()
		{
			updateMazeRandomMouse_init();
			updateMazeWallFollower_init();
		}

		virtual void terminate()
		{
			updateMazeRandomMouse_free();
			updateMazeWallFollower_free();
		}

		virtual unsigned size()
		{
			return 1;
		}

		virtual unsigned memoryUsage()
		{
			return 0;
		}
	};

	struct PledgeAlgorithm : public MazeAlgorithm
	{
		virtual bool update(struct0_T & grid)
		{
			return updateMazePledge(&grid) != 0;
		}

		virtual void init()
		{
			updateMazePledge_init();
		}

		virtual void terminate()
		{
			updateMazePledge_free();
		}

		virtual unsigned size()
		{
			return 1;
		}

		virtual unsigned memoryUsage()
		{
			return 2;
		}
	};

	struct ShortestPathAlgorithm : public MazeAlgorithm
	{
		struct Worker
		{
			unsigned size;
			unsigned position;

			Worker * father;
			std::list<Worker *> children;

			Worker(unsigned p, Worker * f)
				: size(1), position(p), father(f)
			{}
		};

		virtual bool update(struct0_T & grid)
		{
			bool res = updateMazeShortestPathBFS(&grid) != 0;

			unsigned newSize = getMazeShortestPathBFSQueueSize();			

			double * queue = getMazeShortestPathBFSQueue();

			/*
			for(unsigned i(0); i < newSize; ++i)
			{	
				std::cout << queue[i] << ' ';
			}

			std::cout << std::endl;
			*/

			if(newSize == 0) return res;

			if(m_oldSize == newSize)
			{
				//std::cout << "update worker " << m_oldCell->position << " -> " << queue[newSize - 1] << std::endl;
				m_oldCell->position = queue[newSize - 1];
				m_oldCell->size++;
			}

			else if(m_oldSize < newSize)
			{
				if(m_oldSize == 0)
				{
					m_workers.push_back(Worker(queue[0], m_oldCell));
					std::cout << "new worker " << queue[0] << std::endl;
				}
				else
				{
					for(unsigned i(m_oldSize - 1); i < newSize; ++i)
					{
						//std::cout << "new worker " << queue[i] << std::endl;
						m_workers.push_back(Worker(queue[i], m_oldCell));

						m_oldCell->children.push_back(&m_workers.back());
					}
				}
			}
			else if(m_oldSize > newSize)
			{
				//std::cout << "start erasing tree from " << m_oldCell->position << std::endl;
				eraseTree(m_oldCell);
			}

			m_oldSize = newSize;

			unsigned oldId = queue[0];
			for(auto it = m_workers.begin(); it != m_workers.end(); ++it)
			{
				if(it->position == oldId)
				{
					m_oldCell = &(*it);
					break;
				}
			}

			return res;
		}

		void eraseTree(Worker * node)
		{
			Worker * f = node->father;

			//std::cout << "erase cell " << node->position << std::endl;

			if(f != nullptr)
			{
				for(auto it = f->children.begin(); it != f->children.end(); ++it)
				{
					Worker * c = *it;
					if(c->position == node->position)
					{
						f->children.erase(it);
						break;
					}
				}
			}

			for(auto it = m_workers.begin(); it != m_workers.end(); ++it)
			{
				if(it->position == node->position)
				{
					m_workers.erase(it);
					break;
				}
			}

			if(f != nullptr && f->children.size() == 0)
				eraseTree(f);
		}

		virtual void init()
		{
			updateMazeShortestPathBFS_init();

			//m_workers.clear();
			m_memoryUsage = 0;
			m_oldSize = 0;
			m_oldCell = nullptr;
			m_workers.clear();
		}

		virtual void terminate()
		{
			updateMazeShortestPathBFS_free();
		}

		virtual unsigned size()
		{
			return 2;
		}

		virtual unsigned memoryUsage()
		{
			unsigned memory = 0;
			for(auto & w : m_workers)
				memory += w.size;

			return memory;
		}

		private:
			

			unsigned m_oldSize;
			unsigned m_memoryUsage;
			Worker * m_oldCell;

			std::list<Worker> m_workers;
	};
}

#endif