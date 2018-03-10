//
// File: rng.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 04-Oct-2017 10:47:28
//

// Include Files
#include "rt_nonfinite.h"
#include "generateMaze.h"
#include "updateMazePledge.h"
#include "updateMazeRandomMouse.h"
#include "updateMazeShortestPathBFS.h"
#include "updateMazeTremauxs.h"
#include "updateMazeWallFollower.h"
#include "updateStartPosition.h"
#include "rng.h"
#include "generateMaze_data.h"

// Function Definitions

//
// Arguments    : double varargin_1
// Return Type  : void
//
void rng(double varargin_1)
{
  unsigned int r;
  unsigned int b_r;
  int mti;
  if (varargin_1 < 4.294967296E+9) {
    if (varargin_1 >= 0.0) {
      r = (unsigned int)varargin_1;
    } else {
      r = 0U;
    }
  } else if (varargin_1 >= 4.294967296E+9) {
    r = MAX_uint32_T;
  } else {
    r = 0U;
  }

  if (r == 0U) {
    r = 5489U;
  }

  state[0] = r;
  state[624] = 624U;
  b_r = r;
  state[0] = r;
  for (mti = 0; mti < 623; mti++) {
    r = (r ^ r >> 30U) * 1812433253U + (mti + 1);
    state[mti + 1] = r;
    b_r = (b_r ^ b_r >> 30U) * 1812433253U + (mti + 1);
    state[mti + 1] = b_r;
  }

  state[624] = 624U;
}

//
// File trailer for rng.cpp
//
// [EOF]
//
