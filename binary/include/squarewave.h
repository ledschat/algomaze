
#ifndef LEDSCHAT_SQUAREWAVE_H__
#define LEDSCHAT_SQUAREWAVE_H__

#include "ledschat-1.0.h"

#include <vector>

namespace LedsChat
{
	class Squarewave
	{
		public:
			Squarewave(unsigned size);

			void reset  ();
			void update ();
			void draw   (RenderWall & wall);

		private:
			int  getNeighbour (unsigned id, unsigned direction);
			int  discretize   (float in);
		    void printHSV     (int i, int value, int max, int colormax, RenderWall & wall);		    

			struct State
			{
				float localFlow;
			    float qte;
			    float change;

			    float flow[4];
			    int   canFlow[4]; 

			    short myHue;
			    int8_t oldSign;
			};

			std::vector<State> m_matrix;
			unsigned           m_offset;
			unsigned 		   m_size;

			unsigned           m_currentLetter;
			unsigned           m_cpt;

			static constexpr float paramAccellerationTransfer	= 0.01f; 
		    static constexpr float paramPreservationTransfer	= 1.0f; 
		    static constexpr float paramFrictionTransfer		= 0.001f;
		    static constexpr float paramPreservationgreenical	= 0.5f;
		    static constexpr float paramSpringgreenical			= 0.00001f;
		    static constexpr float paramFrictiongreenical		= 0.001f;



	};
}

#endif
