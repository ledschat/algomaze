//
// File: updateMazePledge.cpp
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
static coder_internal_ref currentHead;
static boolean_T currentHead_not_empty;
static double startPos;
static boolean_T startPos_not_empty;
static coder_internal_ref b_curPos;
static boolean_T b_curPos_not_empty;
static coder_internal_ref angularSum;
static boolean_T angularSum_not_empty;
static coder_internal_ref_1 b_lastMoves;
static boolean_T b_lastMoves_not_empty;
static coder_internal_ref_2 b_lastMovesColors;
static boolean_T b_lastMovesColors_not_empty;


// Function Declarations
static void turnLeft(coder_internal_ref *c_curPos, coder_internal_ref_5 *offset,
                     coder_internal_ref *b_currentHead, coder_internal_ref
                     *b_angularSum, coder_internal_ref *front, const
                     coder_internal_ref_4 *maze);

// Function Definitions

//
// Arguments    : coder_internal_ref *c_curPos
//                coder_internal_ref_5 *offset
//                coder_internal_ref *b_currentHead
//                coder_internal_ref *b_angularSum
//                coder_internal_ref *front
//                const coder_internal_ref_4 *maze
// Return Type  : void
//
static void turnLeft(coder_internal_ref *c_curPos, coder_internal_ref_5 *offset,
                     coder_internal_ref *b_currentHead, coder_internal_ref
                     *b_angularSum, coder_internal_ref *front, const
                     coder_internal_ref_4 *maze)
{
  double curIdx;
  int i5;
  coder_internal_ref *d_curPos;
  coder_internal_ref_5 *b_offset;
  coder_internal_ref *c_currentHead;
  switch ((int)b_currentHead->contents) {
   case 1:
    // Up
    b_currentHead->contents = 2.0;
    break;

   case 2:
    // Left
    b_currentHead->contents = 3.0;
    break;

   case 3:
    // Down
    b_currentHead->contents = 4.0;
    break;

   case 4:
    // Right
    b_currentHead->contents = 1.0;
    break;
  }

  curIdx = b_angularSum->contents - 1.0;
  b_angularSum->contents = curIdx;
  curIdx = b_currentHead->contents;
  switch ((int)curIdx) {
   case 1:
    i5 = 1;
    break;

   case 2:
    i5 = 2;
    break;

   case 3:
    i5 = 3;
    break;

   case 4:
    i5 = 4;
    break;
  }

  front->contents = i5;
  if (maze->contents.grid->data[(int)(c_curPos->contents + offset->contents[(int)
       front->contents - 1]) - 1] != maze->contents.Wall) {
    //  We have already turned. Try moving one step
    d_curPos = c_curPos;
    b_offset = offset;
    c_currentHead = b_currentHead;
    curIdx = d_curPos->contents + b_offset->contents[(int)
      c_currentHead->contents - 1];
    d_curPos->contents = curIdx;
  }
}

//
// Arguments    : void
// Return Type  : void
//
void startPos_not_empty_init()
{
  startPos_not_empty = false;
}

//
// SOLVEMAZEPLEDGE Summary of this function goes here
//    Detailed explanation goes here
// Arguments    : struct0_T *maze
// Return Type  : boolean_T
//
boolean_T updateMazePledge(struct0_T *maze)
{
  boolean_T solved;
  coder_internal_ref_4 b_maze;
  int i;
  double lastMovesLength;
  boolean_T y;
  boolean_T x[2];
  int loop_ub;
  boolean_T exitg1;
  double dv1[4];
  double idxForFadeMap;
  coder_internal_ref_5 offset;
  int i8;
  coder_internal_ref front;
  int right;
  emxArray_real_T *r9;
  coder_internal_ref_1 *d_lastMoves;
  int i9;
  emxArray_int32_T *r10;
  e_emxInitStruct_coder_internal_(&b_maze);
  emxCopyStruct_struct0_T(&b_maze.contents, maze);

  //  Pick a random direction
  //  1 - Up
  //  2 - Left
  //  3 - Down
  //  4 - Right
  solved = false;
  if (!currentHead_not_empty) {
    currentHead_not_empty = true;
    currentHead.contents = 4.0;

    // choose right
    for (i = 0; i < 4; i++) {
      b_maze.contents.grid->data[(int)b_maze.contents.start[i] - 1] = 2.0;
    }

    // no wall
  }

  if (!startPos_not_empty) {
    //  The maze start is given by a 2x2 square, select bottom left corner.
    startPos = b_maze.contents.start[2];
    startPos_not_empty = true;
  }

  if (!b_curPos_not_empty) {
    b_curPos_not_empty = true;
    b_curPos.contents = startPos;
  }

  if (!angularSum_not_empty) {
    angularSum_not_empty = true;
    angularSum.contents = 0.0;
  }

  //  We need a variable to store the last moves such that we can have a fading
  //  effect for the cursor
  //  This variable will store what colors each of the moves gets.
  if (!b_lastMoves_not_empty) {
    //  We multiply by three because we want to repeat the non-white colors three times. 
    lastMovesLength = (b_maze.contents.fadingColorMapEnd -
                       b_maze.contents.fadingColorMapStart) * 3.0 + 1.0;

    //  Setup the colors used for the last moves
    if (!b_lastMovesColors_not_empty) {
      b_lastMovesColors_not_empty = true;
    }

    i = b_lastMovesColors.contents->size[0] * b_lastMovesColors.contents->size[1];
    b_lastMovesColors.contents->size[0] = 1;
    b_lastMovesColors.contents->size[1] = (int)lastMovesLength;
    emxEnsureCapacity((emxArray__common *)b_lastMovesColors.contents, i, sizeof
                      (double));
    loop_ub = (int)lastMovesLength;
    for (i = 0; i < loop_ub; i++) {
      b_lastMovesColors.contents->data[i] = 0.0;
    }

    idxForFadeMap = b_maze.contents.fadingColorMapStart;
    for (i = 0; i < (int)lastMovesLength; i++) {
      b_lastMovesColors.contents->data[i] = idxForFadeMap;
      if (b_mod(1.0 + (double)i) == 0.0) {
        idxForFadeMap++;
      }
    }

    //  Grid space
    //  Color value
    if (!b_lastMoves_not_empty) {
      b_lastMoves_not_empty = true;
    }

    i = b_lastMoves.contents->size[0] * b_lastMoves.contents->size[1];
    b_lastMoves.contents->size[0] = 2;
    b_lastMoves.contents->size[1] = (int)lastMovesLength;
    emxEnsureCapacity((emxArray__common *)b_lastMoves.contents, i, sizeof(double));
    loop_ub = (int)lastMovesLength;
    for (i = 0; i < loop_ub; i++) {
      b_lastMoves.contents->data[b_lastMoves.contents->size[0] * i] = rtNaN;
    }

    loop_ub = b_lastMovesColors.contents->size[1];
    for (i = 0; i < loop_ub; i++) {
      b_lastMoves.contents->data[1 + b_lastMoves.contents->size[0] * i] =
        b_lastMovesColors.contents->data[b_lastMovesColors.contents->size[0] * i];
    }
  }

  lastMovesLength = b_curPos.contents;
  for (i = 0; i < 2; i++) {
    x[i] = (lastMovesLength == b_maze.contents.exit[i]);
  }

  y = false;
  loop_ub = 0;
  exitg1 = false;
  while ((!exitg1) && (loop_ub < 2)) {
    if (x[loop_ub]) {
      y = true;
      exitg1 = true;
    } else {
      loop_ub++;
    }
  }

  if (y) {
    solved = true;

    // currentHead = []; curPos = []; angularSum = [];
  } else {
    //  The offsets so we can find the adjacent elements
    dv1[0] = -1.0;
    dv1[1] = -b_maze.contents.numRows;
    dv1[2] = 1.0;
    dv1[3] = b_maze.contents.numRows;
    for (i = 0; i < 4; i++) {
      offset.contents[i] = dv1[i];
    }

    if (angularSum.contents == 0.0) {
      lastMovesLength = currentHead.contents;
      switch ((int)lastMovesLength) {
       case 1:
        i8 = 1;
        break;

       case 2:
        i8 = 2;
        break;

       case 3:
        i8 = 3;
        break;

       case 4:
        i8 = 4;
        break;
      }

      front.contents = i8;
      if (b_maze.contents.grid->data[(int)(b_curPos.contents + offset.contents
           [(int)front.contents - 1]) - 1] != b_maze.contents.Wall) {
        //  We can move
        lastMovesLength = b_curPos.contents + offset.contents[(int)
          currentHead.contents - 1];
        b_curPos.contents = lastMovesLength;
      } else {
        // Hit a wall, turn left first so wall is on right.
        turnLeft(&b_curPos, &offset, &currentHead, &angularSum, &front, &b_maze);
      }
    } else {
      // We are in pledge algorithm
      //  Get the left and right moves based on our current heading
      lastMovesLength = currentHead.contents;
      switch ((int)lastMovesLength) {
       case 1:
        i8 = 1;
        right = 3;
        break;

       case 2:
        i8 = 2;
        right = 0;
        break;

       case 3:
        i8 = 3;
        right = 1;
        break;

       case 4:
        i8 = 4;
        right = 2;
        break;
      }

      front.contents = i8;

      // Check right side first.
      if (b_maze.contents.grid->data[(int)(b_curPos.contents +
           offset.contents[right]) - 1] != b_maze.contents.Wall) {
        switch ((int)currentHead.contents) {
         case 1:
          // Up
          currentHead.contents = 4.0;
          break;

         case 2:
          // Left
          currentHead.contents = 1.0;
          break;

         case 3:
          // Down
          currentHead.contents = 2.0;
          break;

         case 4:
          // Right
          currentHead.contents = 3.0;
          break;
        }

        lastMovesLength = angularSum.contents + 1.0;
        angularSum.contents = lastMovesLength;
        lastMovesLength = currentHead.contents;
        switch ((int)lastMovesLength) {
         case 1:
          i9 = 1;
          break;

         case 2:
          i9 = 2;
          break;

         case 3:
          i9 = 3;
          break;

         case 4:
          i9 = 4;
          break;
        }

        front.contents = i9;
        if (b_maze.contents.grid->data[(int)(b_curPos.contents +
             offset.contents[(int)front.contents - 1]) - 1] !=
            b_maze.contents.Wall) {
          //  We have already turned. Try moving one step
          lastMovesLength = b_curPos.contents + offset.contents[(int)
            currentHead.contents - 1];
          b_curPos.contents = lastMovesLength;
        }
      } else if (b_maze.contents.grid->data[(int)(b_curPos.contents +
                  offset.contents[(int)front.contents - 1]) - 1] !=
                 b_maze.contents.Wall) {
        lastMovesLength = b_curPos.contents + offset.contents[(int)
          currentHead.contents - 1];
        b_curPos.contents = lastMovesLength;
      } else {
        turnLeft(&b_curPos, &offset, &currentHead, &angularSum, &front, &b_maze);
      }
    }

    emxInit_real_T1(&r9, 1);

    //  Update the maze image
    d_lastMoves = &b_lastMoves;
    i = b_lastMoves.contents->size[0] * b_lastMoves.contents->size[1];
    b_lastMoves.contents->size[0] = 2;
    emxEnsureCapacity((emxArray__common *)b_lastMoves.contents, i, sizeof(double));
    i = b_lastMoves.contents->size[0];
    i8 = b_lastMoves.contents->size[1];
    i9 = r9->size[0];
    r9->size[0] = i * i8;
    emxEnsureCapacity((emxArray__common *)r9, i9, sizeof(double));
    loop_ub = i * i8;
    for (i = 0; i < loop_ub; i++) {
      r9->data[i] = b_lastMoves.contents->data[i];
    }

    loop_ub = r9->size[0];
    for (i = 0; i < loop_ub; i++) {
      d_lastMoves->contents->data[i] = r9->data[i];
    }

    emxFree_real_T(&r9);
    emxInit_int32_T(&r10, 1);
    circshift(d_lastMoves->contents);
    loop_ub = b_lastMoves.contents->size[1];
    i = r10->size[0];
    r10->size[0] = loop_ub;
    emxEnsureCapacity((emxArray__common *)r10, i, sizeof(int));
    for (i = 0; i < loop_ub; i++) {
      r10->data[i] = i;
    }

    loop_ub = b_lastMovesColors.contents->size[1];
    for (i = 0; i < loop_ub; i++) {
      b_lastMoves.contents->data[1 + b_lastMoves.contents->size[0] * r10->data[i]]
        = b_lastMovesColors.contents->data[b_lastMovesColors.contents->size[0] *
        i];
    }

    emxFree_int32_T(&r10);
    b_lastMoves.contents->data[0] = b_curPos.contents;
    i = b_lastMoves.contents->size[1];
    if (2 > i) {
      loop_ub = 2;
    } else {
      loop_ub = i;
    }

    if (i == 0) {
      i = 0;
    } else {
      i = loop_ub;
    }

    for (loop_ub = 0; loop_ub < i; loop_ub++) {
      //  For each last move we want to get the ajacent pixes and set
      //  them all to the given value.
      lastMovesLength = b_lastMoves.contents->data[b_lastMoves.contents->size[0]
        * loop_ub];
      if (!rtIsNaN(lastMovesLength)) {
        //  Make sure it is valid
        b_maze.contents.grid->data[(int)b_lastMoves.contents->
          data[b_lastMoves.contents->size[0] * loop_ub] - 1] =
          b_lastMoves.contents->data[1 + b_lastMoves.contents->size[0] * loop_ub];
      }
    }
  }

  emxCopyStruct_struct0_T(maze, &b_maze.contents);
  e_emxFreeStruct_coder_internal_(&b_maze);
  return solved;
}

//
// Arguments    : void
// Return Type  : void
//
void updateMazePledge_free()
{
  c_emxFreeStruct_coder_internal_(&b_lastMovesColors);
  d_emxFreeStruct_coder_internal_(&b_lastMoves);
}

//
// Arguments    : void
// Return Type  : void
//
void updateMazePledge_init()
{
  c_emxInitStruct_coder_internal_(&b_lastMovesColors);
  d_emxInitStruct_coder_internal_(&b_lastMoves);
  b_lastMovesColors_not_empty = false;
  b_lastMoves_not_empty = false;
  angularSum_not_empty = false;
  b_curPos_not_empty = false;
  currentHead_not_empty = false;
}

//
// File trailer for updateMazePledge.cpp
//
// [EOF]
//
