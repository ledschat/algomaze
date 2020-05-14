//
// File: updateMazeRandomMouse.cpp
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
#include "any1.h"
#include "circshift.h"
#include "rand.h"

// Type Definitions
typedef struct {
  double contents[3];
} coder_internal_ref_3;

// Variable Definitions
static coder_internal_ref b_currentPos;
static boolean_T b_currentPos_not_empty;
static double currentDirection;
static boolean_T currentDirection_not_empty;
static coder_internal_ref_1 c_lastMoves;
static boolean_T c_lastMoves_not_empty;
static coder_internal_ref_2 c_lastMovesColors;
static boolean_T c_lastMovesColors_not_empty;

// Function Declarations
static void updateLastMovesColors(coder_internal_ref_1 *d_lastMoves, const
  coder_internal_ref_2 *d_lastMovesColors, const coder_internal_ref
  *c_currentPos, const coder_internal_ref_3 *offsetForRemainingPixels,
  coder_internal_ref_4 *maze);

// Function Definitions

//
// Arguments    : coder_internal_ref_1 *d_lastMoves
//                const coder_internal_ref_2 *d_lastMovesColors
//                const coder_internal_ref *c_currentPos
//                const coder_internal_ref_3 *offsetForRemainingPixels
//                coder_internal_ref_4 *maze
// Return Type  : void
//
static void updateLastMovesColors(coder_internal_ref_1 *d_lastMoves, const
  coder_internal_ref_2 *d_lastMovesColors, const coder_internal_ref
  *c_currentPos, const coder_internal_ref_3 *offsetForRemainingPixels,
  coder_internal_ref_4 *maze)
{
  emxArray_real_T *r3;
  int i6;
  int loop_ub;
  emxArray_int32_T *r4;
  emxArray_real_T *e_lastMovesColors;
  int y;
  double x;
  double px[4];
  emxInit_real_T(&r3, 2);
  i6 = r3->size[0] * r3->size[1];
  r3->size[0] = 2;
  r3->size[1] = d_lastMoves->contents->size[1];
  emxEnsureCapacity((emxArray__common *)r3, i6, sizeof(double));
  loop_ub = d_lastMoves->contents->size[0] * d_lastMoves->contents->size[1];
  for (i6 = 0; i6 < loop_ub; i6++) {
    r3->data[i6] = d_lastMoves->contents->data[i6];
  }

  circshift(r3);
  i6 = d_lastMoves->contents->size[0] * d_lastMoves->contents->size[1];
  d_lastMoves->contents->size[0] = 2;
  d_lastMoves->contents->size[1] = r3->size[1];
  emxEnsureCapacity((emxArray__common *)d_lastMoves->contents, i6, sizeof(double));
  loop_ub = r3->size[0] * r3->size[1];
  for (i6 = 0; i6 < loop_ub; i6++) {
    d_lastMoves->contents->data[i6] = r3->data[i6];
  }

  emxFree_real_T(&r3);
  emxInit_int32_T(&r4, 1);
  loop_ub = d_lastMoves->contents->size[1];
  i6 = r4->size[0];
  r4->size[0] = loop_ub;
  emxEnsureCapacity((emxArray__common *)r4, i6, sizeof(int));
  for (i6 = 0; i6 < loop_ub; i6++) {
    r4->data[i6] = i6;
  }

  emxInit_real_T(&e_lastMovesColors, 2);
  i6 = e_lastMovesColors->size[0] * e_lastMovesColors->size[1];
  e_lastMovesColors->size[0] = 1;
  e_lastMovesColors->size[1] = d_lastMovesColors->contents->size[1];
  emxEnsureCapacity((emxArray__common *)e_lastMovesColors, i6, sizeof(double));
  loop_ub = d_lastMovesColors->contents->size[1];
  for (i6 = 0; i6 < loop_ub; i6++) {
    e_lastMovesColors->data[e_lastMovesColors->size[0] * i6] =
      d_lastMovesColors->contents->data[d_lastMovesColors->contents->size[0] *
      i6];
  }

  loop_ub = e_lastMovesColors->size[1];
  for (i6 = 0; i6 < loop_ub; i6++) {
    d_lastMoves->contents->data[1 + d_lastMoves->contents->size[0] * r4->data[i6]]
      = e_lastMovesColors->data[e_lastMovesColors->size[0] * i6];
  }

  emxFree_real_T(&e_lastMovesColors);
  emxFree_int32_T(&r4);
  d_lastMoves->contents->data[0] = c_currentPos->contents;
  loop_ub = d_lastMoves->contents->size[1];
  if (2 > loop_ub) {
    y = 2;
  } else {
    y = loop_ub;
  }

  if (loop_ub == 0) {
    loop_ub = 0;
  } else {
    loop_ub = y;
  }

  for (y = 0; y < loop_ub; y++) {
    //  For each last move we want to get the ajacent pixes and set
    //  them all to the given value.
    x = d_lastMoves->contents->data[d_lastMoves->contents->size[0] * y];
    if (!rtIsNaN(x)) {
      //  Make sure it is valid
      x = d_lastMoves->contents->data[d_lastMoves->contents->size[0] * y];
      px[0] = d_lastMoves->contents->data[d_lastMoves->contents->size[0] * y];
      for (i6 = 0; i6 < 3; i6++) {
        px[i6 + 1] = x + offsetForRemainingPixels->contents[i6];
      }

      x = d_lastMoves->contents->data[1 + d_lastMoves->contents->size[0] * y];
      for (i6 = 0; i6 < 4; i6++) {
        maze->contents.grid->data[(int)px[i6] - 1] = x;
      }
    }
  }
}

//
// Arguments    : void
// Return Type  : void
//
void currentDirection_not_empty_init()
{
  currentDirection_not_empty = false;
}

//
// Solve the maze using Random Mouse algorithm
// Arguments    : struct0_T *maze
// Return Type  : boolean_T
//
boolean_T updateMazeRandomMouse(struct0_T *maze)
{
  boolean_T solved;
  coder_internal_ref_4 b_maze;
  coder_internal_ref_3 offsetForRemainingPixels;
  double lastMovesLength;
  int i10;
  double neighbors[4];
  int loop_ub;
  double idxForFadeMap;
  int idx;
  int ii;
  boolean_T exitg1;
  boolean_T b[4];
  int possibleNeighbors[4];
  signed char ii_data[4];
  boolean_T c_maze[4];
  signed char possibleIndices_data[4];
  boolean_T tf;
  int exponent;
  int tmp_data[4];
  boolean_T p;
  e_emxInitStruct_coder_internal_(&b_maze);
  emxCopyStruct_struct0_T(&b_maze.contents, maze);

  //  Used to find the adjacent elements
  offsetForRemainingPixels.contents[0] = 1.0;
  offsetForRemainingPixels.contents[1] = maze->numRows;
  offsetForRemainingPixels.contents[2] = maze->numRows + 1.0;
  if (!b_currentPos_not_empty) {
    b_currentPos_not_empty = true;
    b_currentPos.contents = maze->start[0];
  }

  //  We need a variable to store the current direction that we are traveling
  //  so that we only randomly pick a direction
  if (!currentDirection_not_empty) {
    lastMovesLength = b_rand();
    currentDirection = 1.0 + std::floor(lastMovesLength * 4.0);
    currentDirection_not_empty = true;

    //  1 - left
    //  2 - up
    //  3 - right
    //  4 - down
  }

  //  We need a variable to store the last moves such that we can have a fading
  //  effect for the cursor
  //  This variable will store what colors each of the moves gets.
  if (!c_lastMoves_not_empty) {
    //  We multiply by three because we want to repeat the non-white colors three times. 
    lastMovesLength = (maze->fadingColorMapEnd - maze->fadingColorMapStart) *
      2.0 + 1.0;

    //  Setup the colors used for the last moves
    if (!c_lastMovesColors_not_empty) {
      c_lastMovesColors_not_empty = true;
    }

    i10 = c_lastMovesColors.contents->size[0] * c_lastMovesColors.contents->
      size[1];
    c_lastMovesColors.contents->size[0] = 1;
    c_lastMovesColors.contents->size[1] = (int)lastMovesLength;
    emxEnsureCapacity((emxArray__common *)c_lastMovesColors.contents, i10,
                      sizeof(double));
    loop_ub = (int)lastMovesLength;
    for (i10 = 0; i10 < loop_ub; i10++) {
      c_lastMovesColors.contents->data[i10] = 0.0;
    }

    idxForFadeMap = maze->fadingColorMapStart;
    for (idx = 0; idx < (int)lastMovesLength; idx++) {
      c_lastMovesColors.contents->data[idx] = idxForFadeMap;
      if (c_mod(1.0 + (double)idx) == 0.0) {
        idxForFadeMap++;
      }
    }

    //  Grid space
    //  Color value
    if (!c_lastMoves_not_empty) {
      c_lastMoves_not_empty = true;
    }

    i10 = c_lastMoves.contents->size[0] * c_lastMoves.contents->size[1];
    c_lastMoves.contents->size[0] = 2;
    c_lastMoves.contents->size[1] = (int)lastMovesLength;
    emxEnsureCapacity((emxArray__common *)c_lastMoves.contents, i10, sizeof
                      (double));
    loop_ub = (int)lastMovesLength;
    for (i10 = 0; i10 < loop_ub; i10++) {
      c_lastMoves.contents->data[c_lastMoves.contents->size[0] * i10] = rtNaN;
    }

    loop_ub = c_lastMovesColors.contents->size[1];
    for (i10 = 0; i10 < loop_ub; i10++) {
      c_lastMoves.contents->data[1 + c_lastMoves.contents->size[0] * i10] =
        c_lastMovesColors.contents->data[c_lastMovesColors.contents->size[0] *
        i10];
    }
  }

  solved = false;

  //  maze.grid(maze.start) = 5;
  //  Mark the current position as visited
  //  maze.grid(allPixels) = 3; %visited
  updateLastMovesColors(&c_lastMoves, &c_lastMovesColors, &b_currentPos,
                        &offsetForRemainingPixels, &b_maze);

  //  Get the adjacent squares
  neighbors[0] = b_currentPos.contents + -maze->numRows;
  neighbors[1] = b_currentPos.contents + -1.0;
  neighbors[2] = b_currentPos.contents + 1.0;
  neighbors[3] = b_currentPos.contents + maze->numRows;

  // remove neighbors out of maze
  //   temp = neighbors>maze.numCols*maze.numRows;
  //   neighbors(temp)=[];
  //   temp = neighbors<1;
  //   neighbors(temp)=[];
  //
  //  possibleNeighbors = neighbors(maze.grid(neighbors) ~= maze.Wall);%Not a wall 
  for (idx = 0; idx < 4; idx++) {
    lastMovesLength = rtNaN;
    if ((neighbors[idx] > 1.0) && (neighbors[idx] <= b_maze.contents.numCols *
         b_maze.contents.numRows) && (b_maze.contents.grid->data[(int)
         neighbors[idx] - 1] != b_maze.contents.Wall)) {
      lastMovesLength = neighbors[idx];
    }

    idxForFadeMap = rtNaN;
    if (!rtIsNaN(lastMovesLength)) {
      possibleNeighbors[0] = (int)lastMovesLength - 1;
      for (i10 = 0; i10 < 3; i10++) {
        possibleNeighbors[i10 + 1] = (int)(lastMovesLength +
          offsetForRemainingPixels.contents[i10]) - 1;
      }

      for (i10 = 0; i10 < 4; i10++) {
        c_maze[i10] = (b_maze.contents.grid->data[possibleNeighbors[i10]] ==
                       b_maze.contents.Wall);
      }

      if (!c_any(c_maze)) {
        idxForFadeMap = lastMovesLength;
      }
    }

    b[idx] = rtIsNaN(idxForFadeMap);
    neighbors[idx] = idxForFadeMap;
  }

  idx = 0;
  ii = 1;
  exitg1 = false;
  while ((!exitg1) && (ii < 5)) {
    if (!b[ii - 1]) {
      idx++;
      ii_data[idx - 1] = (signed char)ii;
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
    ii = 0;
  } else {
    loop_ub = idx;
    ii = idx;
  }

  for (i10 = 0; i10 < loop_ub; i10++) {
    possibleIndices_data[i10] = ii_data[i10];
  }

  if (ii > 0) {
    //  First check if we have hit a dead end. If so, turn around.
    if (ii == 1) {
      //  Go the only possible route
      currentDirection = possibleIndices_data[0];
      lastMovesLength = neighbors[(int)currentDirection - 1];
    } else if (ii > 2) {
      //  We should only pick a random number if the number of possible
      //  neighbors is greater than 2
      lastMovesLength = b_rand();
      lastMovesLength = 1.0 + std::floor(lastMovesLength * (double)loop_ub);
      currentDirection = possibleIndices_data[(int)lastMovesLength - 1];
      lastMovesLength = neighbors[possibleIndices_data[(int)lastMovesLength - 1]
        - 1];
    } else {
      //  We should keep traversing in the direction we are going
      if (!rtIsNaN(neighbors[(int)currentDirection - 1])) {
        lastMovesLength = neighbors[(int)currentDirection - 1];
      } else {
        //  We have come to a bend in the maze. In this case we want go
        //  not the opposite direction of our current direction.
        if (currentDirection == 1.0) {
          //  We are going left
          ii = 0;
          for (idx = 0; idx < 2; idx++) {
            if (possibleIndices_data[idx] != 4) {
              tmp_data[ii] = idx + 1;
              ii++;
            }
          }

          currentDirection = possibleIndices_data[tmp_data[0] - 1];
        } else if (currentDirection == 2.0) {
          //  We are going up
          ii = 0;
          for (idx = 0; idx < 2; idx++) {
            if (possibleIndices_data[idx] != 3) {
              tmp_data[ii] = idx + 1;
              ii++;
            }
          }

          currentDirection = possibleIndices_data[tmp_data[0] - 1];
        } else if (currentDirection == 3.0) {
          //  We are going down
          ii = 0;
          for (idx = 0; idx < 2; idx++) {
            if (possibleIndices_data[idx] != 2) {
              tmp_data[ii] = idx + 1;
              ii++;
            }
          }

          currentDirection = possibleIndices_data[tmp_data[0] - 1];
        } else {
          //  We are going right
          ii = 0;
          for (idx = 0; idx < 2; idx++) {
            if (possibleIndices_data[idx] != 1) {
              tmp_data[ii] = idx + 1;
              ii++;
            }
          }

          currentDirection = possibleIndices_data[tmp_data[0] - 1];
        }

        lastMovesLength = neighbors[(int)currentDirection - 1];
      }
    }

    b_currentPos.contents = lastMovesLength;
  }

  //  Check if we have solved the maze.
  idxForFadeMap = b_currentPos.contents;
  tf = false;
  ii = 0;
  exitg1 = false;
  while ((!exitg1) && (ii + 1 < 3)) {
    lastMovesLength = std::abs(b_maze.contents.exit[ii] / 2.0);
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

    if ((std::abs(b_maze.contents.exit[ii] - idxForFadeMap) < lastMovesLength) ||
        (rtIsInf(idxForFadeMap) && rtIsInf(b_maze.contents.exit[ii]) &&
         ((idxForFadeMap > 0.0) == (b_maze.contents.exit[ii] > 0.0)))) {
      p = true;
    } else {
      p = false;
    }

    if (p) {
      tf = true;
      exitg1 = true;
    } else {
      ii++;
    }
  }

  if (tf) {
    // solved
    solved = true;
    updateLastMovesColors(&c_lastMoves, &c_lastMovesColors, &b_currentPos,
                          &offsetForRemainingPixels, &b_maze);
  }

  emxCopyStruct_struct0_T(maze, &b_maze.contents);
  e_emxFreeStruct_coder_internal_(&b_maze);
  return solved;
}

//
// Arguments    : void
// Return Type  : void
//
void updateMazeRandomMouse_free()
{
  c_emxFreeStruct_coder_internal_(&c_lastMovesColors);
  d_emxFreeStruct_coder_internal_(&c_lastMoves);
}

//
// Arguments    : void
// Return Type  : void
//
void updateMazeRandomMouse_init()
{
  c_emxInitStruct_coder_internal_(&c_lastMovesColors);
  d_emxInitStruct_coder_internal_(&c_lastMoves);
  c_lastMovesColors_not_empty = false;
  c_lastMoves_not_empty = false;
  b_currentPos_not_empty = false;
}

//
// File trailer for updateMazeRandomMouse.cpp
//
// [EOF]
//
