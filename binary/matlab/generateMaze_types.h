//
// File: generateMaze_types.h
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 04-Oct-2017 10:47:28
//
#ifndef GENERATEMAZE_TYPES_H
#define GENERATEMAZE_TYPES_H

// Include Files
#include "rtwtypes.h"

// Type Definitions
typedef struct {
  double contents;
} coder_internal_ref;

#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T

struct emxArray_real_T
{
  double *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 //struct_emxArray_real_T

typedef struct {
  emxArray_real_T *contents;
} coder_internal_ref_1;

typedef struct {
  emxArray_real_T *contents;
} coder_internal_ref_2;

typedef struct {
  emxArray_real_T *grid;
  double exit[2];
  double start[4];
  double NoWall;
  double Wall;
  double numRows;
  double numCols;
  double colorMap[39];
  double fadingColorMapStart;
  double fadingColorMapEnd;
  double BadPath;
  double GoodPath;
  double CurrentPos;
  double StartColor;
} struct0_T;

typedef struct {
  struct0_T contents;
} coder_internal_ref_4;

typedef struct {
  double contents[4];
} coder_internal_ref_5;

#ifndef struct_emxArray__common
#define struct_emxArray__common

struct emxArray__common
{
  void *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 //struct_emxArray__common

#ifndef struct_emxArray_boolean_T
#define struct_emxArray_boolean_T

struct emxArray_boolean_T
{
  boolean_T *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 //struct_emxArray_boolean_T

#ifndef struct_emxArray_int32_T
#define struct_emxArray_int32_T

struct emxArray_int32_T
{
  int *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 //struct_emxArray_int32_T

#ifndef struct_emxArray_int8_T
#define struct_emxArray_int8_T

struct emxArray_int8_T
{
  signed char *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};

#endif                                 //struct_emxArray_int8_T
#endif

//
// File trailer for generateMaze_types.h
//
// [EOF]
//
