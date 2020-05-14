//
// File: ifWhileCond.cpp
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
#include "ifWhileCond.h"

// Function Definitions

//
// Arguments    : const boolean_T x[4]
// Return Type  : boolean_T
//
boolean_T b_ifWhileCond(const boolean_T x[4])
{
  boolean_T y;
  int k;
  boolean_T exitg1;
  y = true;
  k = 1;
  exitg1 = false;
  while ((!exitg1) && (k < 5)) {
    if (!x[k - 1]) {
      y = false;
      exitg1 = true;
    } else {
      k++;
    }
  }

  return y;
}

//
// Arguments    : const boolean_T x[2]
// Return Type  : boolean_T
//
boolean_T ifWhileCond(const boolean_T x[2])
{
  boolean_T y;
  int k;
  boolean_T exitg1;
  y = true;
  k = 1;
  exitg1 = false;
  while ((!exitg1) && (k < 3)) {
    if (!x[k - 1]) {
      y = false;
      exitg1 = true;
    } else {
      k++;
    }
  }

  return y;
}

//
// File trailer for ifWhileCond.cpp
//
// [EOF]
//
