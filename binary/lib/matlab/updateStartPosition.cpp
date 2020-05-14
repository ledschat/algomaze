//
// File: updateStartPosition.cpp
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
#include "generateMaze_rtwutil.h"

// Function Definitions

//
// codegen
// Arguments    : struct0_T *maze
//                double startRow
//                double startCol
// Return Type  : void
//
void updateStartPosition(struct0_T *maze, double startRow, double startCol)
{
  double offsetForRemainingPixels[3];
  int vk;
  double desiredStartPos;
  double allPixels[4];
  int i;
  boolean_T y;
  boolean_T x[4];
  boolean_T exitg1;
  boolean_T done;
  int siz[2];
  if ((startRow >= maze->numRows) || (startCol >= maze->numCols) || (startRow <
       1.0) || (startCol < 1.0)) {
  } else {
    offsetForRemainingPixels[0] = maze->numRows;
    offsetForRemainingPixels[1] = maze->numRows + 1.0;
    offsetForRemainingPixels[2] = 1.0;
    vk = (int)startRow + maze->grid->size[0] * ((int)startCol - 1);
    desiredStartPos = vk;
    allPixels[0] = vk;
    for (i = 0; i < 3; i++) {
      allPixels[i + 1] = (double)vk + offsetForRemainingPixels[i];
    }

    for (vk = 0; vk < 4; vk++) {
      x[vk] = (maze->grid->data[(int)allPixels[vk] - 1] != maze->Wall);
    }

    y = true;
    vk = 0;
    exitg1 = false;
    while ((!exitg1) && (vk < 4)) {
      if (!x[vk]) {
        y = false;
        exitg1 = true;
      } else {
        vk++;
      }
    }

    if (y) {
      for (vk = 0; vk < 4; vk++) {
        maze->grid->data[(int)maze->start[vk] - 1] = maze->NoWall;
      }

      for (vk = 0; vk < 4; vk++) {
        maze->grid->data[(int)allPixels[vk] - 1] = maze->StartColor;
      }

      for (i = 0; i < 4; i++) {
        maze->start[i] = allPixels[i];
      }
    } else {
      done = false;
      while (!done) {
        allPixels[0] = desiredStartPos;
        for (i = 0; i < 3; i++) {
          allPixels[i + 1] = desiredStartPos + offsetForRemainingPixels[i];
        }

        for (vk = 0; vk < 4; vk++) {
          x[vk] = (maze->grid->data[(int)allPixels[vk] - 1] == maze->Wall);
        }

        y = true;
        vk = 0;
        exitg1 = false;
        while ((!exitg1) && (vk < 4)) {
          if (!x[vk]) {
            y = false;
            exitg1 = true;
          } else {
            vk++;
          }
        }

        if (y) {
          for (vk = 0; vk < 2; vk++) {
            siz[vk] = maze->grid->size[vk];
          }

          vk = div_s32((int)desiredStartPos - 1, siz[0]);
          if ((int)desiredStartPos - vk * siz[0] == maze->numRows - 1.0) {
            desiredStartPos--;
          } else {
            if (vk + 1 == maze->numCols - 1.0) {
              desiredStartPos -= maze->numRows;
            }
          }
        } else if ((maze->grid->data[(int)allPixels[0] - 1] == maze->Wall) &&
                   (maze->grid->data[(int)allPixels[2] - 1] == maze->Wall)) {
          desiredStartPos++;
        } else if ((maze->grid->data[(int)allPixels[1] - 1] == maze->Wall) &&
                   (maze->grid->data[(int)allPixels[3] - 1] == maze->Wall)) {
          desiredStartPos--;
        } else if ((maze->grid->data[(int)allPixels[0] - 1] == maze->Wall) &&
                   (maze->grid->data[(int)allPixels[1] - 1] == maze->Wall)) {
          desiredStartPos += maze->numRows;
        } else if ((maze->grid->data[(int)allPixels[2] - 1] == maze->Wall) &&
                   (maze->grid->data[(int)allPixels[3] - 1] == maze->Wall)) {
          desiredStartPos -= maze->numRows;
        } else {
          for (vk = 0; vk < 4; vk++) {
            x[vk] = (maze->grid->data[(int)allPixels[vk] - 1] != maze->Wall);
          }

          y = true;
          vk = 0;
          exitg1 = false;
          while ((!exitg1) && (vk < 4)) {
            if (!x[vk]) {
              y = false;
              exitg1 = true;
            } else {
              vk++;
            }
          }

          if (y) {
            done = true;
          } else {
            // at a corner
            desiredStartPos++;
          }
        }
      }

      for (vk = 0; vk < 4; vk++) {
        maze->grid->data[(int)maze->start[vk] - 1] = maze->NoWall;
      }

      for (vk = 0; vk < 4; vk++) {
        maze->grid->data[(int)allPixels[vk] - 1] = maze->StartColor;
      }

      for (i = 0; i < 4; i++) {
        maze->start[i] = allPixels[i];
      }
    }
  }
}

//
// File trailer for updateStartPosition.cpp
//
// [EOF]
//
