//
// File: updateMazeWallFollower.cpp
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
#include "mod.h"
#include "circshift.h"

// Variable Definitions
static coder_internal_ref currentPos;
static boolean_T currentPos_not_empty;
static coder_internal_ref_1 lastMoves;
static boolean_T lastMoves_not_empty;
static coder_internal_ref_2 lastMovesColors;
static boolean_T lastMovesColors_not_empty;

// Function Definitions

//
// Solve the maze using Tr�maux's algorithm
// Arguments    : struct0_T *maze
// Return Type  : boolean_T
//
boolean_T updateMazeWallFollower(struct0_T *maze)
{
  boolean_T solved;
  struct0_T maze_contents;
  double offsetForNeighbors[4];
  double offsetForTurns[4];
  int i;
  double lastMovesLength;
  double neighbors[4];
  int idx;
  boolean_T bv1[4];
  int loop_ub;
  int ii;
  boolean_T bv2[4];
  boolean_T exitg1;
  boolean_T bv3[4];
  boolean_T bv4[4];
  double idxForFadeMap;
  boolean_T bv5[4];
  boolean_T bv6[4];
  int ii_data[4];
  boolean_T updated;
  int indices_data[4];
  int tmp_data[4];
  emxArray_real_T *r7;
  coder_internal_ref_1 *d_lastMoves;
  int b_tmp_data[4];
  int c_tmp_data[4];
  int d_tmp_data[4];
  emxArray_int32_T *r8;
  int exponent;
  boolean_T p;
  emxInitStruct_struct0_T(&maze_contents);
  emxCopyStruct_struct0_T(&maze_contents, maze);

  //  Used to find the adjacent elements
  offsetForNeighbors[0] = 1.0;
  offsetForNeighbors[1] = -maze->numRows;
  offsetForNeighbors[2] = maze->numRows;
  offsetForNeighbors[3] = -1.0;
  offsetForTurns[0] = 1.0 + maze->numRows;
  offsetForTurns[1] = -maze->numRows + 1.0;
  offsetForTurns[2] = maze->numRows - 1.0;
  offsetForTurns[3] = -1.0 - maze->numRows;
  if (!currentPos_not_empty) {
    //  Also change the maze so that all of the start tiles are maked as "no
    //  wall" execpt the actuall starting position.
    for (i = 0; i < 4; i++) {
      maze_contents.grid->data[(int)maze->start[i] - 1] = maze->NoWall;
    }

    maze_contents.grid->data[(int)maze->start[0] - 1] = 5.0;
    if (!currentPos_not_empty) {
      currentPos_not_empty = true;
    }

    currentPos.contents = maze->start[0];
  }

  //  We need a variable to store the last moves such that we can have a fading
  //  effect for the cursor
  //  This variable will store what colors each of the moves gets.
  if (!lastMoves_not_empty) {
    //  We multiply by three because we want to repeat the non-white colors three times. 
    lastMovesLength = (maze->fadingColorMapEnd - maze->fadingColorMapStart) *
      3.0 + 1.0;

    //  Setup the colors used for the last moves
    if (!lastMovesColors_not_empty) {
      lastMovesColors_not_empty = true;
    }

    i = lastMovesColors.contents->size[0] * lastMovesColors.contents->size[1];
    lastMovesColors.contents->size[0] = 1;
    lastMovesColors.contents->size[1] = (int)lastMovesLength;
    emxEnsureCapacity((emxArray__common *)lastMovesColors.contents, i, sizeof
                      (double));
    loop_ub = (int)lastMovesLength;
    for (i = 0; i < loop_ub; i++) {
      lastMovesColors.contents->data[i] = 0.0;
    }

    idxForFadeMap = maze->fadingColorMapStart;
    for (idx = 0; idx < (int)lastMovesLength; idx++) {
      lastMovesColors.contents->data[idx] = idxForFadeMap;
      if (b_mod(1.0 + (double)idx) == 0.0) {
        idxForFadeMap++;
      }
    }

    //  Grid space
    //  Color value
    if (!lastMoves_not_empty) {
      lastMoves_not_empty = true;
    }

    i = lastMoves.contents->size[0] * lastMoves.contents->size[1];
    lastMoves.contents->size[0] = 2;
    lastMoves.contents->size[1] = (int)lastMovesLength;
    emxEnsureCapacity((emxArray__common *)lastMoves.contents, i, sizeof(double));
    loop_ub = (int)lastMovesLength;
    for (i = 0; i < loop_ub; i++) {
      lastMoves.contents->data[lastMoves.contents->size[0] * i] = rtNaN;
    }

    loop_ub = lastMovesColors.contents->size[1];
    for (i = 0; i < loop_ub; i++) {
      lastMoves.contents->data[1 + lastMoves.contents->size[0] * i] =
        lastMovesColors.contents->data[lastMovesColors.contents->size[0] * i];
    }
  }

  solved = false;
  neighbors[0] = currentPos.contents + -maze->numRows;
  neighbors[1] = currentPos.contents + -1.0;
  neighbors[2] = currentPos.contents + 1.0;
  neighbors[3] = currentPos.contents + maze->numRows;

  // Not a wall and not visited.
  for (i = 0; i < 4; i++) {
    bv1[i] = (maze_contents.grid->data[(int)neighbors[i] - 1] == maze->NoWall);
    bv2[i] = (maze_contents.grid->data[(int)neighbors[i] - 1] != 3.0);
    bv3[i] = (maze_contents.grid->data[(int)neighbors[i] - 1] != 5.0);
    bv4[i] = (maze_contents.grid->data[(int)neighbors[i] - 1] == maze->NoWall);
    bv5[i] = (maze_contents.grid->data[(int)neighbors[i] - 1] != 3.0);
    bv6[i] = (maze_contents.grid->data[(int)neighbors[i] - 1] != 5.0);
  }

  idx = 0;
  ii = 0;
  exitg1 = false;
  while ((!exitg1) && (ii + 1 < 5)) {
    if (bv4[ii] && bv5[ii] && bv6[ii]) {
      idx++;
      ii_data[idx - 1] = ii + 1;
      if (idx >= 4) {
        exitg1 = true;
      } else {
        ii++;
      }
    } else {
      ii++;
    }
  }

  if (1 > idx) {
    loop_ub = 0;
  } else {
    loop_ub = idx;
  }

  for (i = 0; i < loop_ub; i++) {
    indices_data[i] = ii_data[i];
  }

  updated = false;
  for (idx = 0; idx < loop_ub; idx++) {
    ii = 0;
    for (i = 0; i < 4; i++) {
      if (bv1[i] && bv2[i] && bv3[i]) {
        tmp_data[ii] = i + 1;
        ii++;
      }
    }

    if (maze_contents.grid->data[(int)((double)(unsigned int)
         neighbors[tmp_data[idx] - 1] + offsetForNeighbors[indices_data[idx] - 1])
        - 1] == maze->Wall) {
      ii = 0;
      for (i = 0; i < 4; i++) {
        if (bv1[i] && bv2[i] && bv3[i]) {
          b_tmp_data[ii] = i + 1;
          ii++;
        }
      }

      currentPos.contents = (unsigned int)neighbors[b_tmp_data[idx] - 1];
      updated = true;
    }
  }

  //  currentPos = possibleNeighbors(...
  //      maze.grid(possibleNeighbors + offsetForNeighbors(indices)) == maze.Wall); 
  if ((!currentPos_not_empty) || (!updated)) {
    // Reached a corner. time to turn.
    for (idx = 0; idx < loop_ub; idx++) {
      ii = 0;
      for (i = 0; i < 4; i++) {
        if (bv1[i] && bv2[i] && bv3[i]) {
          c_tmp_data[ii] = i + 1;
          ii++;
        }
      }

      if (maze_contents.grid->data[(int)((double)(unsigned int)
           neighbors[c_tmp_data[idx] - 1] + offsetForTurns[indices_data[idx] - 1])
          - 1] == maze->Wall) {
        ii = 0;
        for (i = 0; i < 4; i++) {
          if (bv1[i] && bv2[i] && bv3[i]) {
            d_tmp_data[ii] = i + 1;
            ii++;
          }
        }

        currentPos.contents = (unsigned int)neighbors[d_tmp_data[idx] - 1];
      }
    }

    //       currentPos = possibleNeighbors(...
    //          maze.grid(possibleNeighbors + offsetForTurns(indices)) == maze.Wall); 
  }

  emxInit_real_T1(&r7, 1);

  //  Update the cursor to show the fading effect
  d_lastMoves = &lastMoves;
  i = lastMoves.contents->size[0] * lastMoves.contents->size[1];
  lastMoves.contents->size[0] = 2;
  emxEnsureCapacity((emxArray__common *)lastMoves.contents, i, sizeof(double));
  i = lastMoves.contents->size[0];
  idx = lastMoves.contents->size[1];
  ii = r7->size[0];
  r7->size[0] = i * idx;
  emxEnsureCapacity((emxArray__common *)r7, ii, sizeof(double));
  loop_ub = i * idx;
  for (i = 0; i < loop_ub; i++) {
    r7->data[i] = lastMoves.contents->data[i];
  }

  loop_ub = r7->size[0];
  for (i = 0; i < loop_ub; i++) {
    d_lastMoves->contents->data[i] = r7->data[i];
  }

  emxFree_real_T(&r7);
  emxInit_int32_T(&r8, 1);
  circshift(d_lastMoves->contents);
  loop_ub = lastMoves.contents->size[1];
  i = r8->size[0];
  r8->size[0] = loop_ub;
  emxEnsureCapacity((emxArray__common *)r8, i, sizeof(int));
  for (i = 0; i < loop_ub; i++) {
    r8->data[i] = i;
  }

  loop_ub = lastMovesColors.contents->size[1];
  for (i = 0; i < loop_ub; i++) {
    lastMoves.contents->data[1 + lastMoves.contents->size[0] * r8->data[i]] =
      lastMovesColors.contents->data[lastMovesColors.contents->size[0] * i];
  }

  emxFree_int32_T(&r8);
  lastMoves.contents->data[0] = currentPos.contents;
  idx = lastMoves.contents->size[1];
  if (2 > idx) {
    ii = 2;
  } else {
    ii = idx;
  }

  if (idx == 0) {
    idx = 0;
  } else {
    idx = ii;
  }

  for (ii = 0; ii < idx; ii++) {
    //  For each last move we want to get the ajacent pixes and set
    //  them all to the given value.
    lastMovesLength = lastMoves.contents->data[lastMoves.contents->size[0] * ii];
    if (!rtIsNaN(lastMovesLength)) {
      //  Make sure it is valid
      maze_contents.grid->data[(int)lastMoves.contents->data
        [lastMoves.contents->size[0] * ii] - 1] = lastMoves.contents->data[1 +
        lastMoves.contents->size[0] * ii];
    }
  }

  idxForFadeMap = currentPos.contents;
  updated = false;
  idx = 0;
  exitg1 = false;
  while ((!exitg1) && (idx + 1 < 3)) {
    lastMovesLength = std::abs(maze->exit[idx] / 2.0);
    if ((!rtIsInf(lastMovesLength)) && (!rtIsNaN(lastMovesLength))) {
      if (lastMovesLength <= 2.2250738585072014E-308) {
        lastMovesLength = 4.94065645841247E-324;
      } else {
        frexp(lastMovesLength, &exponent);
        lastMovesLength = std::ldexp(1.0, exponent - 53);
      }
    } else {
      lastMovesLength = rtNaN;
    }

    if ((std::abs(maze->exit[idx] - idxForFadeMap) < lastMovesLength) ||
        (rtIsInf(idxForFadeMap) && rtIsInf(maze->exit[idx]) && ((idxForFadeMap >
           0.0) == (maze->exit[idx] > 0.0)))) {
      p = true;
    } else {
      p = false;
    }

    if (p) {
      updated = true;
      exitg1 = true;
    } else {
      idx++;
    }
  }

  if (updated) {
    maze_contents.grid->data[(int)maze->start[0] - 1] = 5.0;
    solved = true;
  }

  emxCopyStruct_struct0_T(maze, &maze_contents);
  emxFreeStruct_struct0_T(&maze_contents);
  return solved;
}

//
// Arguments    : void
// Return Type  : void
//
void updateMazeWallFollower_free()
{
  c_emxFreeStruct_coder_internal_(&lastMovesColors);
  d_emxFreeStruct_coder_internal_(&lastMoves);
}

//
// Arguments    : void
// Return Type  : void
//
void updateMazeWallFollower_init()
{
  c_emxInitStruct_coder_internal_(&lastMovesColors);
  d_emxInitStruct_coder_internal_(&lastMoves);
  lastMovesColors_not_empty = false;
  lastMoves_not_empty = false;
  currentPos_not_empty = false;
}

//
// File trailer for updateMazeWallFollower.cpp
//
// [EOF]
//
