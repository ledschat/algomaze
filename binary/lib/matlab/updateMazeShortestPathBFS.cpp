//
// File: updateMazeShortestPathBFS.cpp
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
#include "generateMaze_emxutil.h"
#include "ifWhileCond.h"
#include "sum.h"
#include "repmat.h"
#include <iostream>

// Variable Definitions
static emxArray_real_T *b_queue;
static boolean_T b_queue_not_empty;
static double b_queueHead;
static double queueTail;
static coder_internal_ref_2 keyObj;
static boolean_T keyObj_not_empty;
static coder_internal_ref_2 valueObj;
static boolean_T valueObj_not_empty;

unsigned getMazeShortestPathBFSSize()
{
  return (unsigned) (queueTail - b_queueHead);
}

double * getMazeShortestPathBFSQueue()
{
    return b_queue->data + (int)(b_queueHead - 1);
}

unsigned getMazeShortestPathBFSQueueSize()
{
  return unsigned (queueTail - b_queueHead);
}

// Function Definitions

//
// Solve the maze using Tr�maux's algorithm
// Arguments    : struct0_T *maze
// Return Type  : boolean_T
//
boolean_T updateMazeShortestPathBFS(struct0_T *maze)
{
 
  boolean_T solved;
  struct0_T maze_contents;
  double dv2[3];
  double c_offsetForRemainingPixels_cont[3];
  emxArray_real_T *r11;
  double numWalls;
  emxArray_boolean_T *b_maze;
  double dv3[4];
  double absxk;
  int j;
  double possibleNeighbors[4];
  int loop_ub;
  boolean_T tf[4];
  boolean_T b_tf[4];
  emxArray_real_T *r12;
  boolean_T exitg1;
  boolean_T y;
  boolean_T c_tf[2];
  int exponent;
  int i;
  double neighbors[4];
  int position[4];
  emxArray_boolean_T *d_tf;
  int iv1[2];
  double dv4[4];
  int b_exponent;
  boolean_T b0;
  emxInitStruct_struct0_T(&maze_contents);
  emxCopyStruct_struct0_T(&maze_contents, maze);
  solved = false;

  //  Used to find the adjacent elements
  dv2[0] = 1.0;
  dv2[1] = maze->numRows;
  dv2[2] = maze->numRows + 1.0;
  c_offsetForRemainingPixels_cont[0] = 1.0;
  c_offsetForRemainingPixels_cont[1] = maze->numRows;
  c_offsetForRemainingPixels_cont[2] = maze->numRows + 1.0;
  if (!b_queue_not_empty) {
    emxInit_real_T(&r11, 2);
    emxInit_boolean_T(&b_maze, 2);
    repmat(maze->Wall, maze->numRows, maze->numCols, r11);
    j = b_maze->size[0] * b_maze->size[1];
    b_maze->size[0] = maze->grid->size[0];
    b_maze->size[1] = maze->grid->size[1];
    emxEnsureCapacity((emxArray__common *)b_maze, j, sizeof(boolean_T));
    loop_ub = maze->grid->size[0] * maze->grid->size[1];
    for (j = 0; j < loop_ub; j++) {
      b_maze->data[j] = (maze->grid->data[j] == r11->data[j]);
    }

    emxFree_real_T(&r11);
    emxInit_real_T(&r12, 2);
    sum(b_maze, r12);
    numWalls = b_sum(r12);
    j = b_queue->size[0] * b_queue->size[1];
    b_queue->size[0] = 1;
    b_queue->size[1] = (int)(maze->numRows * maze->numCols - numWalls);
    emxEnsureCapacity((emxArray__common *)b_queue, j, sizeof(double));
    loop_ub = (int)(maze->numRows * maze->numCols - numWalls);
    emxFree_boolean_T(&b_maze);
    for (j = 0; j < loop_ub; j++) {
      b_queue->data[j] = 0.0;
    }

    b_queue_not_empty = !(b_queue->size[1] == 0);

    // TODO: This can be further minimized
    if (!keyObj_not_empty) {
      keyObj_not_empty = true;
    }

    j = r12->size[0] * r12->size[1];
    r12->size[0] = 1;
    r12->size[1] = (int)(maze->numRows * maze->numCols - numWalls);
    emxEnsureCapacity((emxArray__common *)r12, j, sizeof(double));
    loop_ub = (int)(maze->numRows * maze->numCols - numWalls);
    for (j = 0; j < loop_ub; j++) {
      r12->data[j] = 0.0;
    }

    j = keyObj.contents->size[0] * keyObj.contents->size[1];
    keyObj.contents->size[0] = 1;
    keyObj.contents->size[1] = r12->size[1];
    emxEnsureCapacity((emxArray__common *)keyObj.contents, j, sizeof(double));
    loop_ub = r12->size[0] * r12->size[1];
    for (j = 0; j < loop_ub; j++) {
      keyObj.contents->data[j] = r12->data[j];
    }

    // TODO: This can be further minimized
    if (!valueObj_not_empty) {
      valueObj_not_empty = true;
    }

    j = r12->size[0] * r12->size[1];
    r12->size[0] = 1;
    r12->size[1] = (int)(maze->numRows * maze->numCols - numWalls);
    emxEnsureCapacity((emxArray__common *)r12, j, sizeof(double));
    loop_ub = (int)(maze->numRows * maze->numCols - numWalls);
    for (j = 0; j < loop_ub; j++) {
      r12->data[j] = 0.0;
    }

    j = valueObj.contents->size[0] * valueObj.contents->size[1];
    valueObj.contents->size[0] = 1;
    valueObj.contents->size[1] = r12->size[1];
    emxEnsureCapacity((emxArray__common *)valueObj.contents, j, sizeof(double));
    loop_ub = r12->size[0] * r12->size[1];
    for (j = 0; j < loop_ub; j++) {
      valueObj.contents->data[j] = r12->data[j];
    }

    emxFree_real_T(&r12);

    // TODO: This can be further minimized
    b_queueHead = 1.0;
    queueTail = 2.0;
    b_queue->data[0] = maze->start[0];
    keyObj.contents->data[0] = maze->start[0];
    valueObj.contents->data[0] = -1.0;
  }

  numWalls = b_queue->data[(int)b_queueHead - 1];
  dv3[0] = b_queue->data[(int)b_queueHead - 1];
  absxk = b_queue->data[(int)b_queueHead - 1];
  possibleNeighbors[0] = b_queue->data[(int)b_queueHead - 1];
  for (j = 0; j < 3; j++) {
    dv3[j + 1] = numWalls + dv2[j];
    possibleNeighbors[j + 1] = absxk + c_offsetForRemainingPixels_cont[j];
  }

  b_queueHead++;
  for (j = 0; j < 4; j++) {
    b_tf[j] = false;
    loop_ub = 0;
    exitg1 = false;
    while ((!exitg1) && (loop_ub + 1 < 5)) {
      absxk = std::abs(maze->start[loop_ub] / 2.0);
      if ((!rtIsInf(absxk)) && (!rtIsNaN(absxk))) {
        if (absxk <= 2.2250738585072014E-308) {
          absxk = 4.94065645841247E-324;
        } else {
          frexp(absxk, &exponent);
          absxk = std::ldexp(1.0, exponent - 53);
        }
      } else {
        absxk = rtNaN;
      }

      if ((std::abs(maze->start[loop_ub] - dv3[j]) < absxk) || (rtIsInf(dv3[j]) &&
           rtIsInf(maze->start[loop_ub]) && ((possibleNeighbors[j] > 0.0) ==
            (maze->start[loop_ub] > 0.0)))) {
        y = true;
      } else {
        y = false;
      }

      if (y) {
        b_tf[j] = true;
        exitg1 = true;
      } else {
        loop_ub++;
      }
    }

    tf[j] = !b_tf[j];
  }

  if (b_ifWhileCond(tf)) {
    for (j = 0; j < 4; j++) {
      maze_contents.grid->data[(int)maze->start[j] - 1] = 5.0;
    }
  }

  for (j = 0; j < 4; j++) {
    maze_contents.grid->data[(int)dv3[j] - 1] = 3.0;
  }

  // Visited
  for (j = 0; j < 2; j++) {
    c_tf[j] = false;
    loop_ub = 0;
    exitg1 = false;
    while ((!exitg1) && (loop_ub + 1 < 5)) {
      frexp((double)(unsigned int)dv3[loop_ub] / 2.0, &i);
      if (std::abs((double)(unsigned int)dv3[loop_ub] - maze->exit[j]) < std::
          ldexp(1.0, i - 53)) {
        c_tf[j] = true;
        exitg1 = true;
      } else {
        loop_ub++;
      }
    }
  }

  y = true;
  loop_ub = 0;
  exitg1 = false;
  while ((!exitg1) && (loop_ub < 2)) {
    if (!c_tf[loop_ub]) {
      y = false;
      exitg1 = true;
    } else {
      loop_ub++;
    }
  }

  if (y) {
    //  Solved
    numWalls = possibleNeighbors[0];
    while (numWalls != -1.0) {
      position[0] = (int)numWalls - 1;
      for (j = 0; j < 3; j++) {
        position[j + 1] = (int)(numWalls + dv2[j]) - 1;
      }

      for (j = 0; j < 4; j++) {
        maze_contents.grid->data[position[j]] = 4.0;
      }

      // Make it red.
      j = -1;
      loop_ub = 0;
      exitg1 = false;
      while ((!exitg1) && (loop_ub + 1 <= keyObj.contents->size[1])) {
        absxk = std::abs(keyObj.contents->data[loop_ub] / 2.0);
        if ((!rtIsInf(absxk)) && (!rtIsNaN(absxk))) {
          if (absxk <= 2.2250738585072014E-308) {
            absxk = 4.94065645841247E-324;
          } else {
            frexp(absxk, &b_exponent);
            absxk = std::ldexp(1.0, b_exponent - 53);
          }
        } else {
          absxk = rtNaN;
        }

        if ((std::abs(keyObj.contents->data[loop_ub] - numWalls) < absxk) ||
            (rtIsInf(numWalls) && rtIsInf(keyObj.contents->data[loop_ub]) &&
             ((numWalls > 0.0) == (keyObj.contents->data[loop_ub] > 0.0)))) {
          y = true;
        } else {
          y = false;
        }

        if (y) {
          j = loop_ub;
          exitg1 = true;
        } else {
          loop_ub++;
        }
      }

      numWalls = valueObj.contents->data[j];
    }

    for (j = 0; j < 4; j++) {
      maze_contents.grid->data[(int)maze->start[j] - 1] = 5.0;
    }

    solved = true;

    //      queue = [];
    //      keyObj = [];
    //      valueObj = [];
    //      mapObj = [];
  } else {
    neighbors[0] = possibleNeighbors[0] + -maze->numRows;
    neighbors[1] = possibleNeighbors[0] + -1.0;
    neighbors[2] = possibleNeighbors[0] + 1.0;
    neighbors[3] = possibleNeighbors[0] + maze->numRows;

    // remove neighbors out of maze
    for (j = 0; j < 4; j++) {
      possibleNeighbors[j] = 0.0;
    }

    emxInit_boolean_T(&d_tf, 2);
    for (i = 0; i < 4; i++) {
      if ((neighbors[i] < maze->numCols * maze->numRows) && (neighbors[i] > 1.0)
          && (maze_contents.grid->data[(int)neighbors[i] - 1] != maze->Wall)) {
        numWalls = neighbors[i];
        for (j = 0; j < 2; j++) {
          iv1[j] = keyObj.contents->size[j];
        }

        j = d_tf->size[0] * d_tf->size[1];
        d_tf->size[0] = 1;
        d_tf->size[1] = iv1[1];
        emxEnsureCapacity((emxArray__common *)d_tf, j, sizeof(boolean_T));
        loop_ub = iv1[1];
        for (j = 0; j < loop_ub; j++) {
          d_tf->data[j] = false;
        }

        for (j = 0; j + 1 <= keyObj.contents->size[1]; j++) {
          absxk = std::abs(numWalls / 2.0);
          if ((!rtIsInf(absxk)) && (!rtIsNaN(absxk))) {
            if (absxk <= 2.2250738585072014E-308) {
              absxk = 4.94065645841247E-324;
            } else {
              frexp(absxk, &b_exponent);
              absxk = std::ldexp(1.0, b_exponent - 53);
            }
          } else {
            absxk = rtNaN;
          }

          if ((std::abs(numWalls - keyObj.contents->data[j]) < absxk) ||
              (rtIsInf(keyObj.contents->data[j]) && rtIsInf(numWalls) &&
               ((keyObj.contents->data[j] > 0.0) == (numWalls > 0.0)))) {
            y = true;
          } else {
            y = false;
          }

          if (y) {
            d_tf->data[j] = true;
          }
        }

        y = false;
        j = 1;
        exitg1 = false;
        while ((!exitg1) && (j <= d_tf->size[1])) {
          b0 = !d_tf->data[j - 1];
          if (!b0) {
            y = true;
            exitg1 = true;
          } else {
            j++;
          }
        }

        if (!y) {
          // Not a wall and not visited.
          possibleNeighbors[i] = neighbors[i];
        }
      }
    }

    emxFree_boolean_T(&d_tf);
    for (j = 0; j < 4; j++) {
      neighbors[j] = 0.0;
    }

    for (i = 0; i < 4; i++) {
      if (possibleNeighbors[i] != 0.0) {
        dv4[0] = possibleNeighbors[i];
        for (j = 0; j < 3; j++) {
          dv4[j + 1] = possibleNeighbors[i] + dv2[j];
        }

        for (j = 0; j < 4; j++) {
          b_tf[j] = (maze_contents.grid->data[(int)dv4[j] - 1] == maze->Wall);
        }

        y = false;
        loop_ub = 0;
        exitg1 = false;
        while ((!exitg1) && (loop_ub < 4)) {
          if (b_tf[loop_ub]) {
            y = true;
            exitg1 = true;
          } else {
            loop_ub++;
          }
        }

        if (!y) {
          neighbors[i] = possibleNeighbors[i];
          for (j = 0; j < 4; j++) {
            maze_contents.grid->data[(int)dv4[j] - 1] = 6.0;
          }
        }
      }
    }

    //      newMap = containers.Map(finalPossibleNeighbors, parent);
    for (i = 0; i < 4; i++) {
      if (neighbors[i] != 0.0) {
        keyObj.contents->data[(int)queueTail - 1] = neighbors[i];
        valueObj.contents->data[(int)queueTail - 1] = (unsigned int)dv3[0];
        b_queue->data[(int)queueTail - 1] = neighbors[i];
        queueTail++;
      }
    }

    //      keyObj = [keyObj finalPossibleNeighbors];
    //      valueObj = [valueObj parents];
    //      queue = [queue, finalPossibleNeighbors];
  }

  emxCopyStruct_struct0_T(maze, &maze_contents);
  emxFreeStruct_struct0_T(&maze_contents);
  return solved;
}

//
// Arguments    : void
// Return Type  : void
//
void updateMazeShortestPathBFS_free()
{
  c_emxFreeStruct_coder_internal_(&valueObj);
  c_emxFreeStruct_coder_internal_(&keyObj);
  emxFree_real_T(&b_queue);
}

//
// Arguments    : void
// Return Type  : void
//
void updateMazeShortestPathBFS_init()
{
  c_emxInitStruct_coder_internal_(&valueObj);
  c_emxInitStruct_coder_internal_(&keyObj);
  emxInit_real_T(&b_queue, 2);
  valueObj_not_empty = false;
  keyObj_not_empty = false;
  b_queue_not_empty = false;
}

//
// File trailer for updateMazeShortestPathBFS.cpp
//
// [EOF]
//
