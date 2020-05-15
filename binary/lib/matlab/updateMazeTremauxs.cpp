//
// File: updateMazeTremauxs.cpp
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
#include "rand.h"
#include "sum.h"
#include "repmat.h"
#include "generateMaze_rtwutil.h"

// Variable Definitions
static double curPos[4];
static boolean_T curPos_not_empty;
static emxArray_real_T *queue;
static boolean_T queue_not_empty;
static double queueHead;


unsigned getMazeTremauxsSize()
{

  return (unsigned) queueHead;
}

// Function Declarations
static void findNonWallNeighbors(const coder_internal_ref_5 *offsets, const
  coder_internal_ref_4 *maze, const double position[4], double
  nonWallNeighbors_data[], int nonWallNeighbors_size[2]);

// Function Definitions

//
// This function will take a position and return an 4xn matrix of
//  neighbors in which n is a max of 4 (one per each direction that
//  is valid). It has 4 rows to represent the position of the next
//  move. 2 of elements are from the previous position and 2 of the
//  elements are for the next neighbor. The reason for this is so
//  that we move just 1 pixel down the path at a time.
// Arguments    : const coder_internal_ref_5 *offsets
//                const coder_internal_ref_4 *maze
//                const double position[4]
//                double nonWallNeighbors_data[]
//                int nonWallNeighbors_size[2]
// Return Type  : void
//
static void findNonWallNeighbors(const coder_internal_ref_5 *offsets, const
  coder_internal_ref_4 *maze, const double position[4], double
  nonWallNeighbors_data[], int nonWallNeighbors_size[2])
{
  double b_offsets;
  int i4;
  double leftNeighbors[2];
  boolean_T empty_non_axis_sizes;
  boolean_T x[2];
  int k;
  boolean_T exitg1;
  double b_leftNeighbors[4];
  int leftNeighbors_size_idx_0;
  int leftNeighbors_size_idx_1;
  double leftNeighbors_data[4];
  int topNeighbors_size_idx_0;
  int topNeighbors_size_idx_1;
  double topNeighbors_data[4];
  int rightNeighbors_size_idx_0;
  int rightNeighbors_size_idx_1;
  double rightNeighbors_data[4];
  int bottomNeighbors_size_idx_1;
  int result;
  double bottomNeighbors_data[4];

  //  We expect position to be a 4x4 representing the current position
  //  The elements of Postion are laid out as follows:
  //    |1 2|
  //    |4 3|
  b_offsets = offsets->contents[0];
  for (i4 = 0; i4 < 2; i4++) {
    leftNeighbors[i4] = position[3 * i4] + b_offsets;
  }

  for (i4 = 0; i4 < 2; i4++) {
    x[i4] = (maze->contents.grid->data[(int)leftNeighbors[i4] - 1] !=
             maze->contents.NoWall);
  }

  empty_non_axis_sizes = false;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 2)) {
    if (x[k]) {
      empty_non_axis_sizes = true;
      exitg1 = true;
    } else {
      k++;
    }
  }

  if (empty_non_axis_sizes) {
    leftNeighbors_size_idx_0 = 0;
    leftNeighbors_size_idx_1 = 0;
  } else {
    b_leftNeighbors[0] = leftNeighbors[0];
    b_leftNeighbors[1] = position[0];
    b_leftNeighbors[2] = position[3];
    b_leftNeighbors[3] = leftNeighbors[1];
    leftNeighbors_size_idx_0 = 4;
    leftNeighbors_size_idx_1 = 1;
    for (i4 = 0; i4 < 4; i4++) {
      leftNeighbors_data[i4] = b_leftNeighbors[i4];
    }
  }

  b_offsets = offsets->contents[1];
  for (i4 = 0; i4 < 2; i4++) {
    leftNeighbors[i4] = position[i4] + b_offsets;
  }

  for (i4 = 0; i4 < 2; i4++) {
    x[i4] = (maze->contents.grid->data[(int)leftNeighbors[i4] - 1] !=
             maze->contents.NoWall);
  }

  empty_non_axis_sizes = false;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 2)) {
    if (x[k]) {
      empty_non_axis_sizes = true;
      exitg1 = true;
    } else {
      k++;
    }
  }

  if (empty_non_axis_sizes) {
    topNeighbors_size_idx_0 = 0;
    topNeighbors_size_idx_1 = 0;
  } else {
    b_leftNeighbors[0] = leftNeighbors[0];
    b_leftNeighbors[1] = leftNeighbors[1];
    b_leftNeighbors[2] = position[1];
    b_leftNeighbors[3] = position[0];
    topNeighbors_size_idx_0 = 4;
    topNeighbors_size_idx_1 = 1;
    for (i4 = 0; i4 < 4; i4++) {
      topNeighbors_data[i4] = b_leftNeighbors[i4];
    }
  }

  b_offsets = offsets->contents[3];
  for (i4 = 0; i4 < 2; i4++) {
    leftNeighbors[i4] = position[1 + i4] + b_offsets;
  }

  for (i4 = 0; i4 < 2; i4++) {
    x[i4] = (maze->contents.grid->data[(int)leftNeighbors[i4] - 1] !=
             maze->contents.NoWall);
  }

  empty_non_axis_sizes = false;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 2)) {
    if (x[k]) {
      empty_non_axis_sizes = true;
      exitg1 = true;
    } else {
      k++;
    }
  }

  if (empty_non_axis_sizes) {
    rightNeighbors_size_idx_0 = 0;
    rightNeighbors_size_idx_1 = 0;
  } else {
    b_leftNeighbors[0] = position[1];
    b_leftNeighbors[1] = leftNeighbors[0];
    b_leftNeighbors[2] = leftNeighbors[1];
    b_leftNeighbors[3] = position[2];
    rightNeighbors_size_idx_0 = 4;
    rightNeighbors_size_idx_1 = 1;
    for (i4 = 0; i4 < 4; i4++) {
      rightNeighbors_data[i4] = b_leftNeighbors[i4];
    }
  }

  b_offsets = offsets->contents[2];
  for (i4 = 0; i4 < 2; i4++) {
    leftNeighbors[i4] = position[2 + i4] + b_offsets;
  }

  for (i4 = 0; i4 < 2; i4++) {
    x[i4] = (maze->contents.grid->data[(int)leftNeighbors[i4] - 1] !=
             maze->contents.NoWall);
  }

  empty_non_axis_sizes = false;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 2)) {
    if (x[k]) {
      empty_non_axis_sizes = true;
      exitg1 = true;
    } else {
      k++;
    }
  }

  if (empty_non_axis_sizes) {
    k = 0;
    bottomNeighbors_size_idx_1 = 0;
  } else {
    b_leftNeighbors[0] = position[3];
    b_leftNeighbors[1] = position[2];
    b_leftNeighbors[2] = leftNeighbors[0];
    b_leftNeighbors[3] = leftNeighbors[1];
    k = 4;
    bottomNeighbors_size_idx_1 = 1;
    for (i4 = 0; i4 < 4; i4++) {
      bottomNeighbors_data[i4] = b_leftNeighbors[i4];
    }
  }

  if (!((leftNeighbors_size_idx_0 == 0) || (leftNeighbors_size_idx_1 == 0))) {
    result = leftNeighbors_size_idx_0;
  } else if (!((topNeighbors_size_idx_0 == 0) || (topNeighbors_size_idx_1 == 0)))
  {
    result = topNeighbors_size_idx_0;
  } else if (!((rightNeighbors_size_idx_0 == 0) || (rightNeighbors_size_idx_1 ==
    0))) {
    result = rightNeighbors_size_idx_0;
  } else if (!((k == 0) || (bottomNeighbors_size_idx_1 == 0))) {
    result = k;
  } else {
    result = leftNeighbors_size_idx_0;
    if (topNeighbors_size_idx_0 > leftNeighbors_size_idx_0) {
      result = topNeighbors_size_idx_0;
    }

    if (rightNeighbors_size_idx_0 > result) {
      result = rightNeighbors_size_idx_0;
    }

    if (k > result) {
      result = k;
    }
  }

  empty_non_axis_sizes = (result == 0);
  if (empty_non_axis_sizes || (!((leftNeighbors_size_idx_0 == 0) ||
        (leftNeighbors_size_idx_1 == 0)))) {
  } else {
    leftNeighbors_size_idx_1 = 0;
  }

  if (empty_non_axis_sizes || (!((topNeighbors_size_idx_0 == 0) ||
        (topNeighbors_size_idx_1 == 0)))) {
  } else {
    topNeighbors_size_idx_1 = 0;
  }

  if (empty_non_axis_sizes || (!((rightNeighbors_size_idx_0 == 0) ||
        (rightNeighbors_size_idx_1 == 0)))) {
  } else {
    rightNeighbors_size_idx_1 = 0;
  }

  if (empty_non_axis_sizes || (!((k == 0) || (bottomNeighbors_size_idx_1 == 0))))
  {
  } else {
    bottomNeighbors_size_idx_1 = 0;
  }

  nonWallNeighbors_size[0] = result;
  nonWallNeighbors_size[1] = ((leftNeighbors_size_idx_1 +
    topNeighbors_size_idx_1) + rightNeighbors_size_idx_1) +
    bottomNeighbors_size_idx_1;
  for (i4 = 0; i4 < leftNeighbors_size_idx_1; i4++) {
    for (k = 0; k < result; k++) {
      nonWallNeighbors_data[k + result * i4] = leftNeighbors_data[k + result *
        i4];
    }
  }

  for (i4 = 0; i4 < topNeighbors_size_idx_1; i4++) {
    for (k = 0; k < result; k++) {
      nonWallNeighbors_data[k + result * (i4 + leftNeighbors_size_idx_1)] =
        topNeighbors_data[k + result * i4];
    }
  }

  for (i4 = 0; i4 < rightNeighbors_size_idx_1; i4++) {
    for (k = 0; k < result; k++) {
      nonWallNeighbors_data[k + result * ((i4 + leftNeighbors_size_idx_1) +
        topNeighbors_size_idx_1)] = rightNeighbors_data[k + result * i4];
    }
  }

  for (i4 = 0; i4 < bottomNeighbors_size_idx_1; i4++) {
    for (k = 0; k < result; k++) {
      nonWallNeighbors_data[k + result * (((i4 + leftNeighbors_size_idx_1) +
        topNeighbors_size_idx_1) + rightNeighbors_size_idx_1)] =
        bottomNeighbors_data[k + result * i4];
    }
  }
}

//
// Arguments    : void
// Return Type  : void
//
void curPos_not_empty_init()
{
  curPos_not_empty = false;
}

//
// Solve the maze using Tr�maux's algorithm
// Arguments    : struct0_T *maze
// Return Type  : boolean_T
//
boolean_T updateMazeTremauxs(struct0_T *maze)
{
  boolean_T exitFound;
  coder_internal_ref_4 b_maze;
  int i;
  emxArray_real_T *r5;
  coder_internal_ref_5 offsets;
  emxArray_boolean_T *c_maze;
  int iy;
  int i2;
  int siz[2];
  emxArray_real_T *r6;
  int x[4];
  double numWalls;
  boolean_T y;
  boolean_T b_x[2];
  int b_y[4];
  boolean_T exitg1;
  boolean_T guard1 = false;
  boolean_T c_y[4];
  boolean_T c_x[16];
  int i1;
  boolean_T bv0[4];
  double possibleNeighbors_data[16];
  double nextIdx;
  e_emxInitStruct_coder_internal_(&b_maze);
  emxCopyStruct_struct0_T(&b_maze.contents, maze);
  if (!curPos_not_empty) {
    for (i = 0; i < 4; i++) {
      curPos[i] = maze->start[i];
    }

    curPos_not_empty = true;
  }

  if (!queue_not_empty) {
    emxInit_real_T(&r5, 2);
    emxInit_boolean_T(&c_maze, 2);
    repmat(maze->Wall, maze->numRows, maze->numCols, r5);
    iy = c_maze->size[0] * c_maze->size[1];
    c_maze->size[0] = maze->grid->size[0];
    c_maze->size[1] = maze->grid->size[1];
    emxEnsureCapacity((emxArray__common *)c_maze, iy, sizeof(boolean_T));
    i2 = maze->grid->size[0] * maze->grid->size[1];
    for (iy = 0; iy < i2; iy++) {
      c_maze->data[iy] = (maze->grid->data[iy] == r5->data[iy]);
    }

    emxFree_real_T(&r5);
    emxInit_real_T(&r6, 2);
    sum(c_maze, r6);
    numWalls = b_sum(r6);
    iy = queue->size[0] * queue->size[1];
    queue->size[0] = 4;
    queue->size[1] = (int)(maze->numRows * maze->numCols - numWalls);
    emxEnsureCapacity((emxArray__common *)queue, iy, sizeof(double));
    i2 = (int)(maze->numRows * maze->numCols - numWalls) << 2;
    emxFree_boolean_T(&c_maze);
    emxFree_real_T(&r6);
    for (iy = 0; iy < i2; iy++) {
      queue->data[iy] = 0.0;
    }

    queue_not_empty = !(queue->size[1] == 0);

    // TODO: This can be further minimized
    for (iy = 0; iy < 4; iy++) {
      queue->data[iy] = maze->start[iy];
    }

    queueHead = 1.0;
  }

  offsets.contents[0] = -maze->numRows;
  offsets.contents[1] = -1.0;
  offsets.contents[2] = 1.0;
  offsets.contents[3] = maze->numRows;

  //  Used to find the adjacent elements
  for (iy = 0; iy < 4; iy++) {
    b_maze.contents.grid->data[(int)maze->start[iy] - 1] = maze->StartColor;
  }

  for (iy = 0; iy < 2; iy++) {
    siz[iy] = b_maze.contents.grid->size[iy];
  }

  for (i = 0; i < 4; i++) {
    i2 = div_s32((int)curPos[i] - 1, siz[0]);
    x[i] = (int)curPos[i] - i2 * siz[0];
    b_y[i] = i2 + 1;
  }

  for (i = 0; i < 2; i++) {
    b_x[i] = (x[i] == 1);
  }

  y = true;
  i2 = 0;
  exitg1 = false;
  while ((!exitg1) && (i2 < 2)) {
    if (!b_x[i2]) {
      y = false;
      exitg1 = true;
    } else {
      i2++;
    }
  }

  if (y) {
    exitFound = true;
  } else {
    b_x[0] = (x[2] == maze->numCols);
    b_x[1] = (x[3] == maze->numCols);
    y = true;
    i2 = 0;
    exitg1 = false;
    while ((!exitg1) && (i2 < 2)) {
      if (!b_x[i2]) {
        y = false;
        exitg1 = true;
      } else {
        i2++;
      }
    }

    if (y) {
      exitFound = true;
    } else {
      for (iy = 0; iy < 2; iy++) {
        b_x[iy] = (b_y[3 * iy] == 1);
      }

      y = true;
      i2 = 0;
      exitg1 = false;
      while ((!exitg1) && (i2 < 2)) {
        if (!b_x[i2]) {
          y = false;
          exitg1 = true;
        } else {
          i2++;
        }
      }

      if (y) {
        exitFound = true;
      } else {
        b_x[0] = (b_y[1] == maze->numRows);
        b_x[1] = (b_y[2] == maze->numRows);
        y = true;
        i2 = 0;
        exitg1 = false;
        while ((!exitg1) && (i2 < 2)) {
          if (!b_x[i2]) {
            y = false;
            exitg1 = true;
          } else {
            i2++;
          }
        }

        if (y) {
          for (iy = 0; iy < 4; iy++) {
            for (i2 = 0; i2 < 4; i2++) {
              c_x[i2 + (iy << 2)] = (b_maze.contents.grid->data[(x[i2] +
                b_maze.contents.grid->size[0] * (b_y[iy] - 1)) - 1] ==
                maze->CurrentPos);
            }

            c_y[iy] = false;
          }

          i2 = 0;
          iy = -1;
          for (i = 0; i < 4; i++) {
            i1 = i2 + 1;
            i2 += 4;
            iy++;
            exitg1 = false;
            while ((!exitg1) && (i1 <= i2)) {
              if (c_x[i1 - 1]) {
                c_y[iy] = true;
                exitg1 = true;
              } else {
                i1++;
              }
            }
          }

          y = false;
          i2 = 0;
          exitg1 = false;
          while ((!exitg1) && (i2 < 4)) {
            if (c_y[i2]) {
              y = true;
              exitg1 = true;
            } else {
              i2++;
            }
          }

          if (y) {
            exitFound = true;
          } else {
            exitFound = false;
          }
        } else {
          exitFound = false;
        }
      }
    }
  }

  if (!exitFound) {
    for (i = 0; i < 2; i++) {
      b_x[i] = (x[i] < 1);
    }

    y = true;
    i2 = 0;
    exitg1 = false;
    while ((!exitg1) && (i2 < 2)) {
      if (!b_x[i2]) {
        y = false;
        exitg1 = true;
      } else {
        i2++;
      }
    }

    guard1 = false;
    if (y) {
      guard1 = true;
    } else {
      for (i = 0; i < 2; i++) {
        b_x[i] = (x[i + 2] > maze->numCols);
      }

      y = true;
      i2 = 0;
      exitg1 = false;
      while ((!exitg1) && (i2 < 2)) {
        if (!b_x[i2]) {
          y = false;
          exitg1 = true;
        } else {
          i2++;
        }
      }

      if (y) {
        guard1 = true;
      } else {
        for (iy = 0; iy < 2; iy++) {
          b_x[iy] = (b_y[3 * iy] < 1);
        }

        y = true;
        i2 = 0;
        exitg1 = false;
        while ((!exitg1) && (i2 < 2)) {
          if (!b_x[i2]) {
            y = false;
            exitg1 = true;
          } else {
            i2++;
          }
        }

        if (y) {
          guard1 = true;
        } else {
          for (i = 0; i < 2; i++) {
            b_x[i] = (b_y[i + 1] > maze->numRows);
          }

          y = true;
          i2 = 0;
          exitg1 = false;
          while ((!exitg1) && (i2 < 2)) {
            if (!b_x[i2]) {
              y = false;
              exitg1 = true;
            } else {
              i2++;
            }
          }

          if (y) {
            guard1 = true;
          } else {
            for (iy = 0; iy < 4; iy++) {
              c_y[iy] = ((b_maze.contents.grid->data[(int)curPos[iy] - 1] ==
                          maze->NoWall) || (b_maze.contents.grid->data[(int)
                          curPos[iy] - 1] == maze->StartColor));
              bv0[iy] = (b_maze.contents.grid->data[(int)curPos[iy] - 1] ==
                         maze->CurrentPos);
            }

            y = false;
            i2 = 0;
            exitg1 = false;
            while ((!exitg1) && (i2 < 4)) {
              if (c_y[i2] || bv0[i2]) {
                y = true;
                exitg1 = true;
              } else {
                i2++;
              }
            }

            if (!y) {
              do {
                //  If the space has already been visited mark it as a bad path. 
                for (iy = 0; iy < 4; iy++) {
                  b_maze.contents.grid->data[(int)curPos[iy] - 1] =
                    b_maze.contents.BadPath;
                }

                //  We need to backtrack
                for (iy = 0; iy < 4; iy++) {
                  curPos[iy] = queue->data[iy + queue->size[0] * ((int)queueHead
                    - 1)];
                }

                queueHead--;

                // Get valid adjacent moves
                findNonWallNeighbors(&offsets, &b_maze, curPos,
                                     possibleNeighbors_data, siz);

                // return;
              } while (!(siz[1] >= 1));

              for (iy = 0; iy < 4; iy++) {
                b_maze.contents.grid->data[(int)curPos[iy] - 1] =
                  b_maze.contents.GoodPath;
              }

              numWalls = b_rand();
              nextIdx = c_rand();
              queueHead++;

              // Put parent in queue
              for (iy = 0; iy < 4; iy++) {
                queue->data[iy + queue->size[0] * ((int)queueHead - 1)] =
                  curPos[iy];
              }

              iy = (int)(1.0 + std::floor(nextIdx * (1.0 + std::floor(numWalls *
                (double)siz[1]))));
              for (i2 = 0; i2 < 4; i2++) {
                curPos[i2] = possibleNeighbors_data[i2 + siz[0] * (iy - 1)];
              }
            } else {
              for (iy = 0; iy < 4; iy++) {
                c_y[iy] = (b_maze.contents.grid->data[(int)curPos[iy] - 1] ==
                           maze->Wall);
              }

              y = false;
              i2 = 0;
              exitg1 = false;
              while ((!exitg1) && (i2 < 4)) {
                if (c_y[i2]) {
                  y = true;
                  exitg1 = true;
                } else {
                  i2++;
                }
              }

              if (y) {
                //  We have hit a wall.
                for (iy = 0; iy < 4; iy++) {
                  curPos[iy] = queue->data[iy + queue->size[0] * ((int)queueHead
                    - 1)];
                }

                queueHead--;
              } else {
                // newVars = maze.grid(curPos) ~= maze.BadPath;
                for (iy = 0; iy < 4; iy++) {
                  b_maze.contents.grid->data[(int)curPos[iy] - 1] =
                    maze->GoodPath;
                }

                // Visited
                //  Get valid adjacent moves
                findNonWallNeighbors(&offsets, &b_maze, curPos,
                                     possibleNeighbors_data, siz);

                //  If we have no neighbors keep the same curPos

                if (siz[1] >= 1) {
                  numWalls = b_rand();
                  nextIdx = c_rand();
                  queueHead++;

                  // Put parent in queue
                  for (iy = 0; iy < 4; iy++) {
                    queue->data[iy + queue->size[0] * ((int)queueHead - 1)] =
                      curPos[iy];
                  }

                  iy = (int)(1.0 + std::floor(nextIdx * (1.0 + std::floor
                    (numWalls * (double)siz[1]))));
                  for (i2 = 0; i2 < 4; i2++) {
                    curPos[i2] = possibleNeighbors_data[i2 + siz[0] * (iy - 1)];
                  }

                  for (iy = 0; iy < 4; iy++) {
                    b_maze.contents.grid->data[(int)curPos[iy] - 1] =
                      b_maze.contents.CurrentPos;
                  }

                  // purple color
                }
              }
            }
          }
        }
      }
    }

    if (guard1) {
      //  We are outside of the grid and need to backtrack
      for (iy = 0; iy < 4; iy++) {
        curPos[iy] = queue->data[iy + queue->size[0] * ((int)queueHead - 1)];
      }

      queueHead--;
    }
  }

  emxCopyStruct_struct0_T(maze, &b_maze.contents);
  e_emxFreeStruct_coder_internal_(&b_maze);
  return exitFound;
}

//
// Arguments    : void
// Return Type  : void
//
void updateMazeTremauxs_free()
{
  emxFree_real_T(&queue);
}

//
// Arguments    : void
// Return Type  : void
//
void updateMazeTremauxs_init()
{
  emxInit_real_T(&queue, 2);
  queue_not_empty = false;

}

//
// File trailer for updateMazeTremauxs.cpp
//
// [EOF]
//
