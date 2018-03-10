//
// File: circshift.cpp
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
#include "circshift.h"
#include "generateMaze_emxutil.h"

// Function Definitions

//
// Arguments    : emxArray_real_T *a
// Return Type  : void
//
void circshift(emxArray_real_T *a)
{
  int ns;
  boolean_T shiftright;
  emxArray_real_T *buffer;
  int nv;
  int i7;
  int j;
  int k;
  if (a->size[1] != 0) {
    ns = 1;
    shiftright = true;
    if (1 > (a->size[1] >> 1)) {
      ns = a->size[1] - 1;
      shiftright = false;
    }

    emxInit_real_T(&buffer, 2);
    nv = (int)std::floor((double)a->size[1] / 2.0);
    i7 = buffer->size[0] * buffer->size[1];
    buffer->size[0] = 1;
    buffer->size[1] = nv;
    emxEnsureCapacity((emxArray__common *)buffer, i7, sizeof(double));
    for (i7 = 0; i7 < nv; i7++) {
      buffer->data[i7] = 0.0;
    }

    nv = a->size[1];
    if ((a->size[1] > 1) && (ns > 0)) {
      for (j = 0; j < 2; j++) {
        if (shiftright) {
          for (k = 0; k + 1 <= ns; k++) {
            buffer->data[k] = a->data[j + (((k + nv) - ns) << 1)];
          }

          for (k = nv; k >= ns + 1; k--) {
            a->data[j + ((k - 1) << 1)] = a->data[j + (((k - ns) - 1) << 1)];
          }

          for (k = 0; k + 1 <= ns; k++) {
            a->data[j + (k << 1)] = buffer->data[k];
          }
        } else {
          for (k = 0; k + 1 <= ns; k++) {
            buffer->data[k] = a->data[j + (k << 1)];
          }

          i7 = nv - ns;
          for (k = 0; k + 1 <= i7; k++) {
            a->data[j + (k << 1)] = a->data[j + ((k + ns) << 1)];
          }

          for (k = 0; k + 1 <= ns; k++) {
            a->data[j + (((k + nv) - ns) << 1)] = buffer->data[k];
          }
        }
      }
    }

    emxFree_real_T(&buffer);
  }
}

//
// File trailer for circshift.cpp
//
// [EOF]
//
