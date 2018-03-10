
#include "blueAgent.h"
#include "matlab/updateStartPosition.h"
#include "mazeSound.h"

#ifdef __unix__
#include <termios.h>
#endif

#include <ctime>



#define NS LedsChat::BlueAgent

NS::BlueAgent(Maze & maze, const StartData & data)
	: m_running(true), m_serialOpened(false), m_usedMemory(0), m_time(0), m_currentTmp(0), m_newData(false), m_errors(0),
	  m_currentAlgorithm(0), m_previousState(false), m_received(0), m_waitStart(0)
	  
{
	m_algos.push_back(std::make_unique<RandomMouseAlgorithm>());
	m_algos.push_back(std::make_unique<WallFollowerAlgorithm>());
	m_algos.push_back(std::make_unique<PledgeAlgorithm>());
	m_algos.push_back(std::make_unique<TremauxAlgorithm>());
	m_algos.push_back(std::make_unique<ShortestPathAlgorithm>());


	m_algos[m_currentAlgorithm]->init();

	m_soundBuffer.loadFromMemory(mazeSound, sizeof(mazeSound));
	m_sound.setBuffer(m_soundBuffer);

	setMaze(maze, data);

	m_tty.push_back("/dev/ttyACM0");
	m_tty.push_back("/dev/ttyACM1");
	m_tty.push_back("/dev/ttyACM2");
	m_tty.push_back("/dev/ttyACM3");
	m_tty.push_back("/dev/ttyACM4");
	m_tty.push_back("/dev/ttyACM5");
	m_tty.push_back("/dev/ttyUSB0");
	m_tty.push_back("/dev/ttyUSB1");
	m_tty.push_back("/dev/ttyUSB2");
	m_tty.push_back("/dev/ttyUSB3");
	m_tty.push_back("/dev/ttyUSB4");
	m_tty.push_back("/dev/ttyUSB5");

}

NS::~BlueAgent()
{
	 m_algos[m_currentAlgorithm]->terminate();
}

void NS::setMaze(Maze & maze, const StartData & data)
{
	m_maze = &maze;
	m_startPosition = data.position;	

	reset();
}

void NS::setLuminosity(float lum)
{
	m_luminosity = lum;
}

std::string NS::currentDateTime() 
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}


bool NS::serial()
{
	bool result = false;

	#ifdef __unix__

	if(!m_serialOpened)
	{
		for(unsigned i(0); i < m_tty.size(); ++i)
		{
			m_serialFd = open(m_tty[i].c_str(), O_RDWR | O_NOCTTY | O_NDELAY);

			if(m_serialFd != -1)
			{
				m_serialOpened = true;
				fcntl(m_serialFd, F_SETFL, FNDELAY);

				struct termios toptions;

				tcgetattr(m_serialFd, &toptions);
				cfsetispeed(&toptions, B9600);
				cfsetospeed(&toptions, B9600);
				toptions.c_cflag &= ~PARENB;
				toptions.c_cflag &= ~CSTOPB;
				toptions.c_cflag &= ~CSIZE;
				toptions.c_cflag |= CS8;
				toptions.c_cflag &= ~CRTSCTS;
				toptions.c_cflag |= CREAD | CLOCAL;
				toptions.c_iflag &= ~(IXON | IXOFF | IXANY);
				toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
				toptions.c_oflag &= ~OPOST;
				toptions.c_cc[VMIN] = 1;
				toptions.c_cc[VTIME] = 0;

				cfmakeraw(&toptions);
				tcsetattr(m_serialFd, TCSANOW, &toptions);
				usleep(1000*1000);

				break;
			}
		}
	}
	
	if(m_serialOpened)
	{
		
		int receivedThisCycle = 0;
		int val = read(m_serialFd, m_tmp + m_currentTmp, 6 - m_currentTmp);


		while(val > 0)
		{
			m_received += val;

			receivedThisCycle += val;

			m_currentTmp += val;

			if(m_currentTmp == 6)
			{
				m_tmp[6] = '\0';
				

				if(m_tmp[5] != '\n')
				{
					m_tmp[0] = m_tmp[5];
					m_currentTmp = 1;

					if(++m_errors == 100)
					{
						close(m_serialFd);

						m_errors = 0;

						usleep(1000*1000);

						return false;
					}
				}
				else
				{
					m_errors = 0;
					m_currentTmp = 0;

					m_tmp[6] = '\0';


					unsigned buttonState = m_tmp[0] - '0';
					unsigned algorithm   = m_tmp[2] - '0';
					
					if(algorithm != m_currentAlgorithm && algorithm <= 4)
					{
						// page event
						reset(algorithm);
						result = true;
					}

					if(m_previousState != buttonState && buttonState == 1)
					{
						// button event
						bool oldRunning = m_running;
						reset();
						if(!oldRunning)
							start();

						result = true;
					}

					m_previousState = buttonState;
			
				}


			}

			val = read(m_serialFd, m_tmp + m_currentTmp, 6 - m_currentTmp);
		}

		if(errno != EAGAIN)
		{
			close(m_serialFd);
			m_serialOpened = false;

			return false;
		}

		if(receivedThisCycle == 0)
		{
			m_waitStart++;
			if(m_waitStart == 200)
			{
				close(m_serialFd);
				m_serialOpened = false;
				m_waitStart = 0;

				usleep(1000*1000);

				return false;
			}
		}
		else
			m_waitStart = 0;

		if(m_received >= 12)
		{
			m_received  -= 12;

			if(m_newData)
			{
				m_newData = false;

				std::ostringstream os;

				unsigned minutes = m_time / 60;
				unsigned seconds = m_time % 60;

				unsigned elapsedTime = (minutes * 100 + seconds);

				os << std::setfill('0') << std::setw(4) << (elapsedTime > 9999 ? 9999 : elapsedTime) << ';' << std::setfill('0') 
				                        << std::setw(4) << (m_usedMemory > 9999 ? 9999 : m_usedMemory) << ';';// << "\r\n";

				std::string out = os.str();
				
				if(write(m_serialFd, out.c_str(), out.size()) == -1)
				{
					close(m_serialFd);
					m_serialOpened = false;

					return false;
				}
				
			}
		}
		
	}


	#endif

	return result;
}

bool NS::update()
{
	Timepoint now = std::chrono::system_clock::now();
	Micros elapsed = std::chrono::duration_cast<Micros>(now - m_lastUpdate);
	m_lastUpdate = now;

	
	if(m_running)
	{
		if(m_algos[m_currentAlgorithm]->update(m_maze->grid()))
		{
			for(auto & c : m_path)
				c = 0;

			m_running = false;

			m_sound.play();
			return false;
		}

		m_micros += elapsed;

		if(m_micros.count() >= 1000000)
		{
			++m_time;
			m_micros = Micros::zero();
			m_newData = true;
		}

		unsigned newMemory = m_algos[m_currentAlgorithm]->memoryUsage();

		if(newMemory != m_usedMemory)
		{
			m_newData = true;
			m_usedMemory = newMemory;
		}

		Vector position;

		for(auto & c : m_path)
		{
			if(c == 0) continue;
			c = c <= 0.1f ? 0.1f : c - 0.01f;
		}

		for(unsigned j = 0; j < m_maze->gridSize() ; j++)
		{
			for(unsigned i = 0 ; i < m_maze->gridSize(); i++)
			{
				
				if(m_maze->grid().grid->data[i + j * m_maze->gridSize()] == m_maze->grid().CurrentPos || 
				   m_maze->grid().grid->data[i + j * m_maze->gridSize()] == m_maze->grid().fadingColorMapStart)
				{

					m_path[j * m_maze->gridSize() + i] = 1.0;
				}
			}

		}	

		return true;		
	}

	return false;


}	

void NS::draw(RenderWall & wall)
{

	if(m_running)
	{
		for(unsigned j = 0; j < m_maze->gridSize() ; j++)
		{
			for(unsigned i = 0 ; i < m_maze->gridSize(); i++)
			{
				float value = m_path[j * m_maze->gridSize() + i];
				if(value > 0)
				{
					wall[j][i].b = static_cast<uint8_t>(LedsChat::map(value, 1.f, 0.1f, 255.f, m_luminosity));		

					if(value < 0.5)
					{
						wall[j][i].r = static_cast<uint8_t>(LedsChat::map(value, 0.5f, 0.1f, 0.f, m_luminosity));
						wall[j][i].g = static_cast<uint8_t>(LedsChat::map(value, 0.5f, 0.1f, 0.f, m_luminosity));
					}
				}
			}
		}
	}
	else
	{
		unsigned x = m_startPosition.x;
		unsigned y = m_startPosition.y;
		wall[y][x].b = 255;

		if(m_algos[m_currentAlgorithm]->size() == 2)
		{
			wall[y + 1][x].b = 255;
			wall[y][x + 1].b = 255;
			wall[y + 1][x + 1].b = 255;	
		}
	}
}

void NS::start()
{
	m_running = true;
}

void NS::stop()
{
	m_running = false;
}

void NS::reset(unsigned nextAlgorithm)
{
	m_algos[m_currentAlgorithm]->terminate();

	m_maze->reset();	

	m_path = std::vector<float>(m_maze->gridSize() * m_maze->gridSize(), 0);


	updateStartPosition(&m_maze->grid(), m_startPosition.x + 1, m_startPosition.y + 1);		

	m_currentAlgorithm = nextAlgorithm;	

	m_algos[m_currentAlgorithm]->init();

	m_running = false;

	m_time = 0;
	m_usedMemory = 0;
	m_newData = true;

	m_micros = Micros::zero();
	m_lastUpdate = std::chrono::system_clock::now();

}

void NS::reset()
{
	reset(m_currentAlgorithm);
}

#undef NS
