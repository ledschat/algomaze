
#ifndef LEDSCHAT_UTILS_H_
#define LEDSCHAT_UTILS_H_

#include <cstdint>
#include <string>

namespace LedsChat
{
	struct Vector
	{
		int32_t x;
		int32_t y;
		
		constexpr Vector(int32_t mx = 0, int32_t my = 0)
			: x(mx), y(my)
		{

		}

		Vector operator +  (const Vector & o) const;
		Vector operator += (const Vector & o);
		bool   operator == (const Vector & o) const;
	};

	struct Rect
	{
		int32_t  x;
		int32_t  y;
		uint32_t w;
		uint32_t h;

		constexpr Rect(int32_t mx, int32_t my, uint32_t mw, uint32_t mh)
			: x(mx), y(my), w(mw), h(mh)
		{

		}
	};

	namespace Directions
	{
		constexpr uint32_t top = 0;
		constexpr uint32_t right = 1;
		constexpr uint32_t bottom = 2;
		constexpr uint32_t left = 3;
		constexpr uint32_t noDirection = 4;

		uint32_t stringToDirection(const std::string & direction);


		constexpr Vector positions[4][2] = 
		{
			{
				Vector(0, -1),
				Vector(1, -1)
			}, 
			{
				Vector(2, 0),
				Vector(2, 1)
			}, 
			{
				Vector(0, 2),
				Vector(1, 2)
			}, 
			{
				Vector(-1, 0),
				Vector(-1, 1)
			}
		};


		constexpr Vector move[4] = 
		{			
			Vector(0, -1),			
			Vector(1, 0),			
			Vector(0, 1),			
			Vector(-1, 0)			
		};
	}	

	enum AgentState
	{
		AgentStopped,
		AgentRunning,
		AgentOut
	};

	float map(float value, float istart, float istop, float ostart, float ostop);

}

#endif