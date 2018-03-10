//
// File: repmat.cpp
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
#include "repmat.h"
#include "generateMaze_emxutil.h"

// Function Definitions

//
// Arguments    : double a
//                double varargin_1
//                double varargin_2
//                emxArray_real_T *b
// Return Type  : void
//
void repmat(double a, double varargin_1, double varargin_2, emxArray_real_T *b)
{
  int i3;
  int loop_ub;
  i3 = b->size[0] * b->size[1];
  b->size[0] = (int)varargin_1;
  b->size[1] = (int)varargin_2;
  emxEnsureCapacity((emxArray__common *)b, i3, sizeof(double));
  loop_ub = (int)varargin_1 * (int)varargin_2;
  for (i3 = 0; i3 < loop_ub; i3++) {
    b->data[i3] = a;
  }
}

//
// File trailer for repmat.cpp
//
// [EOF]
//
