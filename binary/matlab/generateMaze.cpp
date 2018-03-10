//
// File: generateMaze.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 22-Jun-2017 09:03:55
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
#include "any1.h"
#include "rand.h"
#include "generateMaze_emxutil.h"
#include "ifWhileCond.h"
#include "all.h"
#include "mod.h"
#include "rng.h"
#include "generateMaze_rtwutil.h"
#include "time.h"

// Function Declarations
static int div_s32_floor(int numerator, int denominator);

// Function Definitions

//
// Arguments    : int numerator
//                int denominator
// Return Type  : int
//
static int div_s32_floor(int numerator, int denominator)
{
  int quotient;
  unsigned int absNumerator;
  unsigned int absDenominator;
  boolean_T quotientNeedsNegation;
  unsigned int tempAbsQuotient;
  if (denominator == 0) {
    if (numerator >= 0) {
      quotient = MAX_int32_T;
    } else {
      quotient = MIN_int32_T;
    }
  } else {
    if (numerator < 0) {
      absNumerator = ~(unsigned int)numerator + 1U;
    } else {
      absNumerator = (unsigned int)numerator;
    }

    if (denominator < 0) {
      absDenominator = ~(unsigned int)denominator + 1U;
    } else {
      absDenominator = (unsigned int)denominator;
    }

    quotientNeedsNegation = ((numerator < 0) != (denominator < 0));
    tempAbsQuotient = absNumerator / absDenominator;
    if (quotientNeedsNegation) {
      absNumerator %= absDenominator;
      if (absNumerator > 0U) {
        tempAbsQuotient++;
      }

      quotient = -(int)tempAbsQuotient;
    } else {
      quotient = (int)tempAbsQuotient;
    }
  }

  return quotient;
}

//
// See the randome number generator by getting the current time stamp.
// Arguments    : double width
//                struct0_T *maze
// Return Type  : void
//
void generateMaze(double width, struct0_T *maze, double seed)
{
  double numCols;
  double numRows;
  boolean_T needThickerOuterWall;
  emxArray_int8_T *r0;
  int i0;
  int loop_ub;
  emxArray_int8_T *grid;
  int b_grid;
  int i;
  int psiz;
  int i1;
  double startPos_X[4];
  double startPos_Y[4];
  emxArray_real_T *S;
  double c_currentPos[4];
  unsigned int backtrackJuncIdx;
  unsigned int nextJuncIdx;
  double offsets[4];
  double b_exit[2];
  int idx;
  boolean_T x[4];
  boolean_T exitg1;
  signed char ii_data[4];
  emxArray_int8_T *mazeGrid;
  signed char unvistedNeighbors_data[4];
  int i2;
  double next[4];
  unsigned int siz[2];
  int nextCol[4];
  int v1[2];
  int nextRow[4];
  boolean_T c_exit[2];
  double endColIdx[2];
  emxArray_boolean_T *r1;
  emxArray_boolean_T *r2;
  emxArray_int8_T *b_mazeGrid;
  static const double dv0[39] = { 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0,
    0.30196078431372547, 0.50196078431372548, 0.50196078431372548,
    0.90196078431372551, 1.0, 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 0.27843137254901962,
    0.4, 0.58039215686274515, 0.70196078431372544, 0.70196078431372544,
    0.94117647058823528, 1.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 0.70196078431372544,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0 };

  rng(seed);

  //  Constant values
  width += 6.0;

  //  Reduce the size by 2 for now so we can add border at the end. This allows
  //  us to control the maze to genereate only 1 exit.
  numCols = width - 2.0;
  numRows = width - 2.0;
  needThickerOuterWall = false;
  if (b_mod(width - 2.0) == 0.0) {
    //  The width of the maze (minus the outer wall) is a multiple of 3 so we
    //  actaully need to decrease the inner maze size by one and just make
    //  the outer wall on the right and bottom sides bigger.
    //  TODO: We could also leave this space as blanks.
    needThickerOuterWall = true;
    numCols = (width - 2.0) - 1.0;
    numRows = (width - 2.0) - 1.0;
  }

  emxInit_int8_T(&r0, 2);

  //  Define the maze matrix and init to NotVisited
  i0 = r0->size[0] * r0->size[1];
  r0->size[0] = (int)numRows;
  r0->size[1] = (int)numCols;
  emxEnsureCapacity((emxArray__common *)r0, i0, sizeof(signed char));
  loop_ub = (int)numRows * (int)numCols;
  for (i0 = 0; i0 < loop_ub; i0++) {
    r0->data[i0] = 0;
  }

  emxInit_int8_T(&grid, 2);
  i0 = grid->size[0] * grid->size[1];
  grid->size[0] = r0->size[0];
  grid->size[1] = r0->size[1];
  emxEnsureCapacity((emxArray__common *)grid, i0, sizeof(signed char));
  loop_ub = r0->size[0] * r0->size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    grid->data[i0] = 3;
  }

  //  Put a wall in every third space on the board (not including the boundary). 
  if (3 > r0->size[0] - 1) {
    i0 = 0;
    b_grid = 1;
    i = 1;
  } else {
    i0 = 2;
    b_grid = 3;
    i = r0->size[0];
  }

  loop_ub = r0->size[1];
  psiz = div_s32_floor((i - i0) - 2, b_grid) + 1;
  for (i = 0; i < loop_ub; i++) {
    for (i1 = 0; i1 < psiz; i1++) {
      grid->data[(i0 + b_grid * i1) + grid->size[0] * i] = 1;
    }
  }

  if (3 > grid->size[1] - 1) {
    i0 = 0;
    b_grid = 1;
    i = 1;
  } else {
    i0 = 2;
    b_grid = 3;
    i = grid->size[1];
  }

  loop_ub = grid->size[0];
  psiz = div_s32_floor((i - i0) - 2, b_grid) + 1;
  for (i = 0; i < psiz; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      grid->data[i1 + grid->size[0] * (i0 + b_grid * i)] = 1;
    }
  }

  //  Specify the starting position, let's assume that it is the center of the
  //  maze.
  seed = (width - 2.0) / 2.0;

  //  this defines the lower right corner of the 4px wide starting point
  //  From top left (clockwise)
  startPos_X[0] = (seed - 1.0) - 1.0;
  startPos_X[1] = seed - 1.0;
  startPos_X[2] = seed - 1.0;
  startPos_X[3] = (seed - 1.0) - 1.0;
  startPos_Y[0] = (seed - 1.0) - 1.0;
  startPos_Y[1] = (seed - 1.0) - 1.0;
  startPos_Y[2] = seed - 1.0;
  startPos_Y[3] = seed - 1.0;

  //  Mark the start as visited
  for (i0 = 0; i0 < 4; i0++) {
    for (b_grid = 0; b_grid < 4; b_grid++) {
      grid->data[((int)startPos_Y[b_grid] + grid->size[0] * ((int)startPos_X[i0]
        - 1)) - 1] = 4;
    }
  }

  //  Now, lets process the remaining elements of the maze.
  psiz = grid->size[0];
  for (i = 0; i < 4; i++) {
    c_currentPos[i] = (int)startPos_X[i] + psiz * ((int)startPos_Y[i] - 1);
  }

  emxInit_real_T(&S, 2);

  //  Pre-allocate the size of S which is the number of non-wall spaces
  //  This variable keeps track of the idx to place the next junction for backtracking 
  backtrackJuncIdx = 1U;

  //  This variable keeps track of the junction to use next in backtracking
  seed = (numCols - std::floor(numCols / 3.0)) / 2.0;
  seed *= seed;
  i0 = S->size[0] * S->size[1];
  S->size[0] = 4;
  S->size[1] = (int)seed;
  emxEnsureCapacity((emxArray__common *)S, i0, sizeof(double));
  loop_ub = (int)seed << 2;
  for (i0 = 0; i0 < loop_ub; i0++) {
    S->data[i0] = 0.0;
  }

  for (i0 = 0; i0 < 4; i0++) {
    S->data[i0] = c_currentPos[i0];
  }

  nextJuncIdx = 2U;
  offsets[0] = -numRows;
  offsets[1] = -1.0;
  offsets[2] = 1.0;
  offsets[3] = numRows;

  //  Used to find the adjacent elements
  for (i = 0; i < 2; i++) {
    b_exit[i] = 0.0;
  }

  while (backtrackJuncIdx < nextJuncIdx) {
    //  Find our unvisited Neighbors
    //  Find the unvisited neighbors
    for (i0 = 0; i0 < 4; i0++) {
      x[i0] = (grid->data[(int)(c_currentPos[i0] + 3.0 * offsets[i0]) - 1] == 3);
    }

    idx = 0;
    psiz = 1;
    exitg1 = false;
    while ((!exitg1) && (psiz < 5)) {
      if (x[psiz - 1]) {
        idx++;
        ii_data[idx - 1] = (signed char)psiz;
        if (idx >= 4) {
          exitg1 = true;
        } else {
          psiz++;
        }
      } else {
        psiz++;
      }
    }

    if (1 > idx) {
      loop_ub = 0;
    } else {
      loop_ub = idx;
    }

    for (i0 = 0; i0 < loop_ub; i0++) {
      unvistedNeighbors_data[i0] = ii_data[i0];
    }

    if (1 > idx) {
      i2 = 0;
    } else {
      i2 = idx;
    }

    if (!(i2 == 0)) {
      seed = b_rand();
      seed = 1.0 + std::floor(seed * (double)loop_ub);

      //  Make the space between next and curPost, not a wall.
      switch (unvistedNeighbors_data[(int)seed - 1]) {
       case 1:
        //  To the left of the current position
        grid->data[(int)(c_currentPos[0] - numRows) - 1] = 2;
        grid->data[(int)(c_currentPos[1] - numRows) - 1] = 2;
        break;

       case 2:
        //  Above the current position
        grid->data[(int)(c_currentPos[0] - 1.0) - 1] = 2;
        grid->data[(int)(c_currentPos[3] - 1.0) - 1] = 2;
        break;

       case 3:
        //  Below the current position
        grid->data[(int)(c_currentPos[1] + 1.0) - 1] = 2;
        grid->data[(int)(c_currentPos[2] + 1.0) - 1] = 2;
        break;

       case 4:
        //  To the right of the current position
        grid->data[(int)(c_currentPos[2] + numRows) - 1] = 2;
        grid->data[(int)(c_currentPos[3] + numRows) - 1] = 2;
        break;
      }

      seed = 3.0 * offsets[unvistedNeighbors_data[(int)seed - 1] - 1];
      for (i0 = 0; i0 < 4; i0++) {
        next[i0] = c_currentPos[i0] + seed;
      }

      for (i0 = 0; i0 < 2; i0++) {
        siz[i0] = (unsigned int)grid->size[i0];
      }

      //  If "next" is on the perimeter of the grid then we need to mark it
      //  as visited and start to backtrack. Also if we are on the
      //  perimiter overwrite the previous exit and give a new one.
      for (i = 0; i < 4; i++) {
        psiz = div_s32((int)next[i] - 1, (int)siz[0]);
        idx = ((int)next[i] - psiz * (int)siz[0]) - 1;
        nextCol[i] = psiz + 1;
        x[i] = (idx + 1 == 1);
        nextRow[i] = idx + 1;
      }

      if (any(x)) {
        //  We are at the top of the maze.
        for (i0 = 0; i0 < 4; i0++) {
          grid->data[(int)next[i0] - 1] = 4;
        }

        b_exit[0] = next[0];
        b_exit[1] = next[3];
      } else {
        for (i = 0; i < 4; i++) {
          x[i] = (nextRow[i] == numRows);
        }

        if (any(x)) {
          //  We are at the bottom of the maze.
          for (i0 = 0; i0 < 4; i0++) {
            grid->data[(int)next[i0] - 1] = 4;
          }

          b_exit[0] = next[1];
          b_exit[1] = next[2];
        } else {
          for (i = 0; i < 4; i++) {
            x[i] = (nextCol[i] == numCols);
          }

          if (any(x)) {
            //  We are at the right of the maze.
            for (i0 = 0; i0 < 4; i0++) {
              grid->data[(int)next[i0] - 1] = 4;
            }

            b_exit[0] = next[2];
            b_exit[1] = next[3];
          } else {
            for (i = 0; i < 4; i++) {
              x[i] = (nextCol[i] == 1);
            }

            if (any(x)) {
              //  We are at the left of the maze.
              for (i0 = 0; i0 < 4; i0++) {
                grid->data[(int)next[i0] - 1] = 4;
              }

              b_exit[0] = next[0];
              b_exit[1] = next[1];
            } else {
              for (i0 = 0; i0 < 4; i0++) {
                x[i0] = (grid->data[(int)(next[i0] + 3.0 * offsets[i0]) - 1] ==
                         3);
              }

              if (b_any(any(x))) {
                for (i0 = 0; i0 < 4; i0++) {
                  S->data[i0 + S->size[0] * ((int)nextJuncIdx - 1)] = next[i0];
                }

                nextJuncIdx++;
              }

              for (i = 0; i < 4; i++) {
                c_currentPos[i] = next[i];
              }

              for (i0 = 0; i0 < 4; i0++) {
                grid->data[(int)next[i0] - 1] = 4;
              }
            }
          }
        }
      }
    } else {
      for (i0 = 0; i0 < 4; i0++) {
        c_currentPos[i0] = S->data[i0 + S->size[0] * ((int)backtrackJuncIdx - 1)];
      }

      backtrackJuncIdx++;
    }
  }

  emxFree_real_T(&S);

  //  Init the final maze to have the asked for number of columns and rows
  //  since we decreased by 2 at the start.
  numRows += 2.0;
  numCols += 2.0;
  if (needThickerOuterWall) {
    //  Add extra if we found earlier that we need a thicker outer wall.
    numCols++;
    numRows++;
  }

  i0 = r0->size[0] * r0->size[1];
  r0->size[0] = (int)numRows;
  r0->size[1] = (int)numCols;
  emxEnsureCapacity((emxArray__common *)r0, i0, sizeof(signed char));
  loop_ub = (int)numRows * (int)numCols;
  for (i0 = 0; i0 < loop_ub; i0++) {
    r0->data[i0] = 0;
  }

  emxInit_int8_T(&mazeGrid, 2);
  i0 = mazeGrid->size[0] * mazeGrid->size[1];
  mazeGrid->size[0] = r0->size[0];
  mazeGrid->size[1] = r0->size[1];
  emxEnsureCapacity((emxArray__common *)mazeGrid, i0, sizeof(signed char));
  loop_ub = r0->size[0] * r0->size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    mazeGrid->data[i0] = 1;
  }

  //  Insert the grid into the new maze such that it is centered into the
  //  bigger rectange.
  if (needThickerOuterWall) {
    i0 = !(2 > r0->size[0] - 2);
    b_grid = !(2 > r0->size[1] - 2);
    loop_ub = grid->size[1];
    for (i = 0; i < loop_ub; i++) {
      psiz = grid->size[0];
      for (i1 = 0; i1 < psiz; i1++) {
        mazeGrid->data[(i0 + i1) + mazeGrid->size[0] * (b_grid + i)] =
          grid->data[i1 + grid->size[0] * i];
      }
    }
  } else {
    i0 = !(2 > r0->size[0] - 1);
    b_grid = !(2 > r0->size[1] - 1);
    loop_ub = grid->size[1];
    for (i = 0; i < loop_ub; i++) {
      psiz = grid->size[0];
      for (i1 = 0; i1 < psiz; i1++) {
        mazeGrid->data[(i0 + i1) + mazeGrid->size[0] * (b_grid + i)] =
          grid->data[i1 + grid->size[0] * i];
      }
    }
  }

  emxFree_int8_T(&r0);

  //  Insert the maze exit.
  for (i = 0; i < 2; i++) {
    siz[i] = (unsigned int)grid->size[i];
    v1[i] = (int)b_exit[i] - 1;
  }

  //  Convert the exits to the new indices to accomondate inseting the grid.
  //  Additionally, remove the walls for the exits along the outer wall.
  b_grid = grid->size[0];
  for (i = 0; i < 2; i++) {
    psiz = div_s32(v1[i], (int)siz[0]);
    idx = v1[i] - psiz * (int)siz[0];
    endColIdx[i] = psiz + 1;
    c_exit[i] = (idx + 1 == b_grid);
    b_exit[i] = idx + 1;
  }

  if (all(c_exit)) {
    //  The exit is along the bottom of the maze. If we have thicker outer
    //  walls then we have to blow out two walls for the exit.
    //  We need to increment the endColIdx since we have offset by one when
    //  we inset the grid into the maze.
    for (i0 = 0; i0 < 2; i0++) {
      endColIdx[i0]++;
    }

    if (needThickerOuterWall) {
      for (i0 = 0; i0 < 2; i0++) {
        for (b_grid = 0; b_grid < 2; b_grid++) {
          mazeGrid->data[((int)(b_exit[b_grid] + (2.0 + (double)b_grid)) +
                          mazeGrid->size[0] * ((int)endColIdx[i0] - 1)) - 1] = 2;
        }
      }

      //  Save the new endRow exit
      for (i0 = 0; i0 < 2; i0++) {
        b_exit[i0] += 2.0;
      }
    } else {
      for (i0 = 0; i0 < 2; i0++) {
        for (b_grid = 0; b_grid < 2; b_grid++) {
          mazeGrid->data[((int)(b_exit[b_grid] + 1.0) + mazeGrid->size[0] *
                          ((int)endColIdx[i0] - 1)) - 1] = 2;
        }
      }

      for (i0 = 0; i0 < 2; i0++) {
        b_exit[i0]++;
      }
    }
  } else {
    for (i = 0; i < 2; i++) {
      c_exit[i] = (b_exit[i] == 1.0);
    }

    if (all(c_exit)) {
      //  The exit is along the top of the maze. The wall is always 1px thick
      //  at the top.
      //  We need to increment the endColIdx since we have offset by one when
      //  we inset the grid into the maze.
      for (i0 = 0; i0 < 2; i0++) {
        endColIdx[i0]++;
      }

      for (i0 = 0; i0 < 2; i0++) {
        mazeGrid->data[mazeGrid->size[0] * ((int)endColIdx[i0] - 1)] = 2;
      }
    } else {
      b_grid = grid->size[1];
      for (i0 = 0; i0 < 2; i0++) {
        c_exit[i0] = ((int)endColIdx[i0] == b_grid);
      }

      if (all(c_exit)) {
        //  The exit is along the right of the maze. If we have thicker outer
        //  walls then we have to blow out two walls for the exit.
        //  We need to increment the endRowIdx since we have offset by one when
        //  we inset the grid into the maze.
        for (i0 = 0; i0 < 2; i0++) {
          b_exit[i0]++;
        }

        if (needThickerOuterWall) {
          for (i0 = 0; i0 < 2; i0++) {
            for (b_grid = 0; b_grid < 2; b_grid++) {
              mazeGrid->data[((int)b_exit[b_grid] + mazeGrid->size[0] * ((int)
                (endColIdx[i0] + (2.0 + (double)i0)) - 1)) - 1] = 2;
            }
          }

          //  Save the new endCol exit
          for (i0 = 0; i0 < 2; i0++) {
            endColIdx[i0] += 2.0;
          }
        } else {
          for (i0 = 0; i0 < 2; i0++) {
            for (b_grid = 0; b_grid < 2; b_grid++) {
              mazeGrid->data[((int)b_exit[b_grid] + mazeGrid->size[0] * ((int)
                (endColIdx[i0] + 1.0) - 1)) - 1] = 2;
            }
          }

          for (i0 = 0; i0 < 2; i0++) {
            endColIdx[i0]++;
          }
        }
      } else {
        for (i = 0; i < 2; i++) {
          c_exit[i] = (endColIdx[i] == 1.0);
        }

        if (all(c_exit)) {
          //  The exit is along the left of the maze. The wall is always 1px thick 
          //  at the left.
          //  We need to increment the endRowIdx since we have offset by one when 
          //  we inset the grid into the maze.
          for (i0 = 0; i0 < 2; i0++) {
            b_exit[i0]++;
          }

          for (i0 = 0; i0 < 2; i0++) {
            mazeGrid->data[(int)b_exit[i0] - 1] = 2;
          }
        }
      }
    }
  }

  emxFree_int8_T(&grid);
  emxInit_boolean_T(&r1, 2);

  //  Convert all "visited" and no visited to NoWall
  i0 = r1->size[0] * r1->size[1];
  r1->size[0] = mazeGrid->size[0];
  r1->size[1] = mazeGrid->size[1];
  emxEnsureCapacity((emxArray__common *)r1, i0, sizeof(boolean_T));
  loop_ub = mazeGrid->size[0] * mazeGrid->size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    r1->data[i0] = (mazeGrid->data[i0] == 4);
  }

  emxInit_boolean_T(&r2, 2);
  i0 = r2->size[0] * r2->size[1];
  r2->size[0] = mazeGrid->size[0];
  r2->size[1] = mazeGrid->size[1];
  emxEnsureCapacity((emxArray__common *)r2, i0, sizeof(boolean_T));
  loop_ub = mazeGrid->size[0] * mazeGrid->size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    r2->data[i0] = (mazeGrid->data[i0] == 3);
  }

  psiz = r1->size[0] * r1->size[1];
  for (i = 0; i < psiz; i++) {
    if (r1->data[i] || r2->data[i]) {
      mazeGrid->data[i] = 2;
    }
  }

  emxFree_boolean_T(&r2);
  emxFree_boolean_T(&r1);
  numCols -= 6.0;
  numRows -= 6.0;
  if (4 > mazeGrid->size[0] - 3) {
    i0 = 0;
    b_grid = 0;
  } else {
    i0 = 3;
    b_grid = mazeGrid->size[0] - 3;
  }

  if (4 > mazeGrid->size[1] - 3) {
    i = 0;
    i1 = 0;
  } else {
    i = 3;
    i1 = mazeGrid->size[1] - 3;
  }

  emxInit_int8_T(&b_mazeGrid, 2);
  idx = b_mazeGrid->size[0] * b_mazeGrid->size[1];
  b_mazeGrid->size[0] = b_grid - i0;
  b_mazeGrid->size[1] = i1 - i;
  emxEnsureCapacity((emxArray__common *)b_mazeGrid, idx, sizeof(signed char));
  loop_ub = i1 - i;
  for (i1 = 0; i1 < loop_ub; i1++) {
    psiz = b_grid - i0;
    for (idx = 0; idx < psiz; idx++) {
      b_mazeGrid->data[idx + b_mazeGrid->size[0] * i1] = mazeGrid->data[(i0 +
        idx) + mazeGrid->size[0] * (i + i1)];
    }
  }

  i0 = mazeGrid->size[0] * mazeGrid->size[1];
  mazeGrid->size[0] = b_mazeGrid->size[0];
  mazeGrid->size[1] = b_mazeGrid->size[1];
  emxEnsureCapacity((emxArray__common *)mazeGrid, i0, sizeof(signed char));
  loop_ub = b_mazeGrid->size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    psiz = b_mazeGrid->size[0];
    for (b_grid = 0; b_grid < psiz; b_grid++) {
      mazeGrid->data[b_grid + mazeGrid->size[0] * i0] = b_mazeGrid->data[b_grid
        + b_mazeGrid->size[0] * i0];
    }
  }

  emxFree_int8_T(&b_mazeGrid);
  loop_ub = mazeGrid->size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    mazeGrid->data[mazeGrid->size[0] * i0] = 1;
  }

  loop_ub = mazeGrid->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    mazeGrid->data[i0] = 1;
  }

  loop_ub = mazeGrid->size[1];
  psiz = mazeGrid->size[0] - 1;
  for (i0 = 0; i0 < loop_ub; i0++) {
    mazeGrid->data[psiz + mazeGrid->size[0] * i0] = 1;
  }

  loop_ub = mazeGrid->size[0];
  psiz = mazeGrid->size[1] - 1;
  for (i0 = 0; i0 < loop_ub; i0++) {
    mazeGrid->data[i0 + mazeGrid->size[0] * psiz] = 1;
  }

  loop_ub = mazeGrid->size[1];
  psiz = mazeGrid->size[0] - 2;
  for (i0 = 0; i0 < loop_ub; i0++) {
    mazeGrid->data[psiz + mazeGrid->size[0] * i0] = 1;
  }

  loop_ub = mazeGrid->size[0];
  psiz = mazeGrid->size[1] - 2;
  for (i0 = 0; i0 < loop_ub; i0++) {
    mazeGrid->data[i0 + mazeGrid->size[0] * psiz] = 1;
  }

  for (i = 0; i < 2; i++) {
    c_exit[i] = (b_exit[i] > numRows);
  }

  if (ifWhileCond(c_exit)) {
    psiz = mazeGrid->size[0] - 1;
    for (i0 = 0; i0 < 2; i0++) {
      mazeGrid->data[psiz + mazeGrid->size[0] * ((int)endColIdx[i0] - 1)] = 2;
    }

    psiz = mazeGrid->size[0] - 2;
    for (i0 = 0; i0 < 2; i0++) {
      mazeGrid->data[psiz + mazeGrid->size[0] * ((int)endColIdx[i0] - 1)] = 2;
    }

    b_exit[0] = numRows;
    b_exit[1] = numRows;
  } else {
    for (i = 0; i < 2; i++) {
      c_exit[i] = (endColIdx[i] > numCols);
    }

    if (ifWhileCond(c_exit)) {
      psiz = mazeGrid->size[1] - 1;
      for (i0 = 0; i0 < 2; i0++) {
        mazeGrid->data[((int)b_exit[i0] + mazeGrid->size[0] * psiz) - 1] = 2;
      }

      psiz = mazeGrid->size[1] - 2;
      for (i0 = 0; i0 < 2; i0++) {
        mazeGrid->data[((int)b_exit[i0] + mazeGrid->size[0] * psiz) - 1] = 2;
      }

      endColIdx[0] = numCols;
      endColIdx[1] = numCols;
    } else {
      for (i0 = 0; i0 < 2; i0++) {
        for (b_grid = 0; b_grid < 2; b_grid++) {
          mazeGrid->data[((int)b_exit[b_grid] + mazeGrid->size[0] * ((int)
            endColIdx[i0] - 1)) - 1] = 2;
        }
      }
    }
  }

  //  Base Color Map
  //  1 = black
  //  2 = white
  //  3 = blue
  //  4 = red
  //  5 = green
  //  6 = ?
  //  Color map to show fading on the movement
  //  7 - take into account maze color map offset
  //  8
  //  9
  //  10
  //  11
  //  12
  //  13
  // convert to 0..1 range
  //  Store the information to a structure
  i0 = maze->grid->size[0] * maze->grid->size[1];
  maze->grid->size[0] = mazeGrid->size[0];
  maze->grid->size[1] = mazeGrid->size[1];
  emxEnsureCapacity((emxArray__common *)maze->grid, i0, sizeof(double));
  loop_ub = mazeGrid->size[0] * mazeGrid->size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    maze->grid->data[i0] = mazeGrid->data[i0];
  }

  psiz = mazeGrid->size[0];
  for (i = 0; i < 2; i++) {
    maze->exit[i] = (int)b_exit[i] + psiz * ((int)endColIdx[i] - 1);
  }

  psiz = mazeGrid->size[0];
  emxFree_int8_T(&mazeGrid);
  for (i = 0; i < 4; i++) {
    maze->start[i] = (int)(startPos_Y[i] + 1.0) + psiz * ((int)(startPos_X[i] +
      1.0) - 1);
  }

  maze->NoWall = 2.0;
  maze->Wall = 1.0;
  maze->numRows = numRows;
  maze->numCols = numCols;
  for (i0 = 0; i0 < 39; i0++) {
    maze->colorMap[i0] = dv0[i0];
  }

  maze->fadingColorMapStart = 7.0;
  maze->fadingColorMapEnd = 13.0;

  //  Define two constants for highlighting the "Good" path and the "Bad" path
  //  which we didn't end up taking.
  maze->BadPath = 3.0;
  maze->GoodPath = 4.0;
  maze->CurrentPos = 6.0;
  maze->StartColor = 5.0;
}

//
// File trailer for generateMaze.cpp
//
// [EOF]
//
