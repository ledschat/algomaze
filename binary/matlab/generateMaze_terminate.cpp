//
// File: generateMaze_terminate.cpp
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
#include "generateMaze_terminate.h"

// Function Definitions

//
// Arguments    : void
// Return Type  : void
//
void generateMaze_terminate()
{
  updateMazeWallFollower_free();
  updateMazePledge_free();
  updateMazeRandomMouse_free();
  updateMazeShortestPathBFS_free();
  updateMazeTremauxs_free();
}

//
// File trailer for generateMaze_terminate.cpp
//
// [EOF]
//
