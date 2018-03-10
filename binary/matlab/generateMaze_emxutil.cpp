//
// File: generateMaze_emxutil.cpp
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

// Function Declarations
static void emxCopyMatrix_real_T(double dst[2], const double src[2]);
static void emxCopyMatrix_real_T1(double dst[4], const double src[4]);
static void emxCopyMatrix_real_T2(double dst[39], const double src[39]);
static void emxCopy_real_T(emxArray_real_T **dst, emxArray_real_T * const *src);

// Function Definitions

//
// Arguments    : double dst[2]
//                const double src[2]
// Return Type  : void
//
static void emxCopyMatrix_real_T(double dst[2], const double src[2])
{
  int i;
  for (i = 0; i < 2; i++) {
    dst[i] = src[i];
  }
}

//
// Arguments    : double dst[4]
//                const double src[4]
// Return Type  : void
//
static void emxCopyMatrix_real_T1(double dst[4], const double src[4])
{
  int i;
  for (i = 0; i < 4; i++) {
    dst[i] = src[i];
  }
}

//
// Arguments    : double dst[39]
//                const double src[39]
// Return Type  : void
//
static void emxCopyMatrix_real_T2(double dst[39], const double src[39])
{
  int i;
  for (i = 0; i < 39; i++) {
    dst[i] = src[i];
  }
}

//
// Arguments    : emxArray_real_T **dst
//                emxArray_real_T * const *src
// Return Type  : void
//
static void emxCopy_real_T(emxArray_real_T **dst, emxArray_real_T * const *src)
{
  int numElDst;
  int numElSrc;
  int i;
  numElDst = 1;
  numElSrc = 1;
  for (i = 0; i < (*dst)->numDimensions; i++) {
    numElDst *= (*dst)->size[i];
    numElSrc *= (*src)->size[i];
  }

  for (i = 0; i < (*dst)->numDimensions; i++) {
    (*dst)->size[i] = (*src)->size[i];
  }

  emxEnsureCapacity((emxArray__common *)*dst, numElDst, sizeof(double));
  for (i = 0; i < numElSrc; i++) {
    (*dst)->data[i] = (*src)->data[i];
  }
}

//
// Arguments    : coder_internal_ref_2 *pStruct
// Return Type  : void
//
void c_emxFreeStruct_coder_internal_(coder_internal_ref_2 *pStruct)
{
  emxFree_real_T(&pStruct->contents);
}

//
// Arguments    : coder_internal_ref_2 *pStruct
// Return Type  : void
//
void c_emxInitStruct_coder_internal_(coder_internal_ref_2 *pStruct)
{
  emxInit_real_T(&pStruct->contents, 2);
}

//
// Arguments    : coder_internal_ref_1 *pStruct
// Return Type  : void
//
void d_emxFreeStruct_coder_internal_(coder_internal_ref_1 *pStruct)
{
  emxFree_real_T(&pStruct->contents);
}

//
// Arguments    : coder_internal_ref_1 *pStruct
// Return Type  : void
//
void d_emxInitStruct_coder_internal_(coder_internal_ref_1 *pStruct)
{
  emxInit_real_T(&pStruct->contents, 2);
}

//
// Arguments    : coder_internal_ref_4 *pStruct
// Return Type  : void
//
void e_emxFreeStruct_coder_internal_(coder_internal_ref_4 *pStruct)
{
  emxFreeStruct_struct0_T(&pStruct->contents);
}

//
// Arguments    : coder_internal_ref_4 *pStruct
// Return Type  : void
//
void e_emxInitStruct_coder_internal_(coder_internal_ref_4 *pStruct)
{
  emxInitStruct_struct0_T(&pStruct->contents);
}

//
// Arguments    : struct0_T *dst
//                const struct0_T *src
// Return Type  : void
//
void emxCopyStruct_struct0_T(struct0_T *dst, const struct0_T *src)
{
  emxCopy_real_T(&dst->grid, &src->grid);
  emxCopyMatrix_real_T(dst->exit, src->exit);
  emxCopyMatrix_real_T1(dst->start, src->start);
  dst->NoWall = src->NoWall;
  dst->Wall = src->Wall;
  dst->numRows = src->numRows;
  dst->numCols = src->numCols;
  emxCopyMatrix_real_T2(dst->colorMap, src->colorMap);
  dst->fadingColorMapStart = src->fadingColorMapStart;
  dst->fadingColorMapEnd = src->fadingColorMapEnd;
  dst->BadPath = src->BadPath;
  dst->GoodPath = src->GoodPath;
  dst->CurrentPos = src->CurrentPos;
  dst->StartColor = src->StartColor;
}

//
// Arguments    : emxArray__common *emxArray
//                int oldNumel
//                unsigned int elementSize
// Return Type  : void
//
void emxEnsureCapacity(emxArray__common *emxArray, int oldNumel, unsigned int
  elementSize)
{
  int newNumel;
  int i;
  void *newData;
  if (oldNumel < 0) {
    oldNumel = 0;
  }

  newNumel = 1;
  for (i = 0; i < emxArray->numDimensions; i++) {
    newNumel *= emxArray->size[i];
  }

  if (newNumel > emxArray->allocatedSize) {
    i = emxArray->allocatedSize;
    if (i < 16) {
      i = 16;
    }

    while (i < newNumel) {
      if (i > 1073741823) {
        i = MAX_int32_T;
      } else {
        i <<= 1;
      }
    }

    newData = calloc((unsigned int)i, elementSize);
    if (emxArray->data != NULL) {
      memcpy(newData, emxArray->data, elementSize * oldNumel);
      if (emxArray->canFreeData) {
        free(emxArray->data);
      }
    }

    emxArray->data = newData;
    emxArray->allocatedSize = i;
    emxArray->canFreeData = true;
  }
}

//
// Arguments    : struct0_T *pStruct
// Return Type  : void
//
void emxFreeStruct_struct0_T(struct0_T *pStruct)
{
  emxFree_real_T(&pStruct->grid);
}

//
// Arguments    : emxArray_boolean_T **pEmxArray
// Return Type  : void
//
void emxFree_boolean_T(emxArray_boolean_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_boolean_T *)NULL) {
    if (((*pEmxArray)->data != (boolean_T *)NULL) && (*pEmxArray)->canFreeData)
    {
      free((void *)(*pEmxArray)->data);
    }

    free((void *)(*pEmxArray)->size);
    free((void *)*pEmxArray);
    *pEmxArray = (emxArray_boolean_T *)NULL;
  }
}

//
// Arguments    : emxArray_int32_T **pEmxArray
// Return Type  : void
//
void emxFree_int32_T(emxArray_int32_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_int32_T *)NULL) {
    if (((*pEmxArray)->data != (int *)NULL) && (*pEmxArray)->canFreeData) {
      free((void *)(*pEmxArray)->data);
    }

    free((void *)(*pEmxArray)->size);
    free((void *)*pEmxArray);
    *pEmxArray = (emxArray_int32_T *)NULL;
  }
}

//
// Arguments    : emxArray_int8_T **pEmxArray
// Return Type  : void
//
void emxFree_int8_T(emxArray_int8_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_int8_T *)NULL) {
    if (((*pEmxArray)->data != (signed char *)NULL) && (*pEmxArray)->canFreeData)
    {
      free((void *)(*pEmxArray)->data);
    }

    free((void *)(*pEmxArray)->size);
    free((void *)*pEmxArray);
    *pEmxArray = (emxArray_int8_T *)NULL;
  }
}

//
// Arguments    : emxArray_real_T **pEmxArray
// Return Type  : void
//
void emxFree_real_T(emxArray_real_T **pEmxArray)
{
  if (*pEmxArray != (emxArray_real_T *)NULL) {
    if (((*pEmxArray)->data != (double *)NULL) && (*pEmxArray)->canFreeData) {
      free((void *)(*pEmxArray)->data);
    }

    free((void *)(*pEmxArray)->size);
    free((void *)*pEmxArray);
    *pEmxArray = (emxArray_real_T *)NULL;
  }
}

//
// Arguments    : struct0_T *pStruct
// Return Type  : void
//
void emxInitStruct_struct0_T(struct0_T *pStruct)
{
  emxInit_real_T(&pStruct->grid, 2);
}

//
// Arguments    : emxArray_boolean_T **pEmxArray
//                int numDimensions
// Return Type  : void
//
void emxInit_boolean_T(emxArray_boolean_T **pEmxArray, int numDimensions)
{
  emxArray_boolean_T *emxArray;
  int i;
  *pEmxArray = (emxArray_boolean_T *)malloc(sizeof(emxArray_boolean_T));
  emxArray = *pEmxArray;
  emxArray->data = (boolean_T *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int *)malloc((unsigned int)(sizeof(int) * numDimensions));
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

//
// Arguments    : emxArray_int32_T **pEmxArray
//                int numDimensions
// Return Type  : void
//
void emxInit_int32_T(emxArray_int32_T **pEmxArray, int numDimensions)
{
  emxArray_int32_T *emxArray;
  int i;
  *pEmxArray = (emxArray_int32_T *)malloc(sizeof(emxArray_int32_T));
  emxArray = *pEmxArray;
  emxArray->data = (int *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int *)malloc((unsigned int)(sizeof(int) * numDimensions));
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

//
// Arguments    : emxArray_int8_T **pEmxArray
//                int numDimensions
// Return Type  : void
//
void emxInit_int8_T(emxArray_int8_T **pEmxArray, int numDimensions)
{
  emxArray_int8_T *emxArray;
  int i;
  *pEmxArray = (emxArray_int8_T *)malloc(sizeof(emxArray_int8_T));
  emxArray = *pEmxArray;
  emxArray->data = (signed char *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int *)malloc((unsigned int)(sizeof(int) * numDimensions));
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

//
// Arguments    : emxArray_real_T **pEmxArray
//                int numDimensions
// Return Type  : void
//
void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions)
{
  emxArray_real_T *emxArray;
  int i;
  *pEmxArray = (emxArray_real_T *)malloc(sizeof(emxArray_real_T));
  emxArray = *pEmxArray;
  emxArray->data = (double *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int *)malloc((unsigned int)(sizeof(int) * numDimensions));
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

//
// Arguments    : emxArray_real_T **pEmxArray
//                int numDimensions
// Return Type  : void
//
void emxInit_real_T1(emxArray_real_T **pEmxArray, int numDimensions)
{
  emxArray_real_T *emxArray;
  int i;
  *pEmxArray = (emxArray_real_T *)malloc(sizeof(emxArray_real_T));
  emxArray = *pEmxArray;
  emxArray->data = (double *)NULL;
  emxArray->numDimensions = numDimensions;
  emxArray->size = (int *)malloc((unsigned int)(sizeof(int) * numDimensions));
  emxArray->allocatedSize = 0;
  emxArray->canFreeData = true;
  for (i = 0; i < numDimensions; i++) {
    emxArray->size[i] = 0;
  }
}

//
// File trailer for generateMaze_emxutil.cpp
//
// [EOF]
//
