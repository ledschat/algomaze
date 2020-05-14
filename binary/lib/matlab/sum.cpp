//
// File: sum.cpp
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
#include "sum.h"
#include "generateMaze_emxutil.h"

// Function Definitions

//
// Arguments    : const emxArray_real_T *x
// Return Type  : double
//
double b_sum(const emxArray_real_T *x)
{
  double y;
  int k;
  if (x->size[1] == 0) {
    y = 0.0;
  } else {
    y = x->data[0];
    for (k = 2; k <= x->size[1]; k++) {
      y += x->data[k - 1];
    }
  }

  return y;
}

//
// Arguments    : const emxArray_boolean_T *x
//                emxArray_real_T *y
// Return Type  : void
//
void sum(const emxArray_boolean_T *x, emxArray_real_T *y)
{
  int vlen;
  int i;
  int xoffset;
  double s;
  int k;
  vlen = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = x->size[1];
  emxEnsureCapacity((emxArray__common *)y, vlen, sizeof(double));
  if ((x->size[0] == 0) || (x->size[1] == 0)) {
    vlen = y->size[0] * y->size[1];
    y->size[0] = 1;
    emxEnsureCapacity((emxArray__common *)y, vlen, sizeof(double));
    i = y->size[1];
    for (vlen = 0; vlen < i; vlen++) {
      y->data[y->size[0] * vlen] = 0.0;
    }
  } else {
    vlen = x->size[0];
    for (i = 0; i + 1 <= x->size[1]; i++) {
      xoffset = i * vlen;
      s = x->data[xoffset];
      for (k = 2; k <= vlen; k++) {
        s += (double)x->data[(xoffset + k) - 1];
      }

      y->data[i] = s;
    }
  }
}

//
// File trailer for sum.cpp
//
// [EOF]
//
