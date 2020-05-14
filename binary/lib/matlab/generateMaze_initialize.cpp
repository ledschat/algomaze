//
// File: generateMaze_initialize.cpp
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
#include "generateMaze_initialize.h"
#include "eml_rand_mt19937ar_stateful.h"

// Function Definitions

//
// Arguments    : void
// Return Type  : void
//
void generateMaze_initialize()
{
  rt_InitInfAndNaN(8U);
  currentDirection_not_empty_init();
  startPos_not_empty_init();
  curPos_not_empty_init();
  updateMazeWallFollower_init();
  updateMazePledge_init();
  updateMazeRandomMouse_init();
  updateMazeShortestPathBFS_init();
  c_eml_rand_mt19937ar_stateful_i();
  updateMazeTremauxs_init();
}

//
// File trailer for generateMaze_initialize.cpp
//
// [EOF]
//
