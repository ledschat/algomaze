//
// File: main.cpp
//
// MATLAB Coder version            : 3.3
// C/C++ source code generated on  : 02-May-2017 08:07:00
//

//***********************************************************************
// This automatically generated example C main file shows how to call
// entry-point functions that MATLAB Coder generated. You must customize
// this file for your application. Do not modify this file directly.
// Instead, make a copy of this file, modify it, and integrate it into
// your development environment.
//
// This file initializes entry-point function arguments to a default
// size and value before calling the entry-point functions. It does
// not store or use any values returned from the entry-point functions.
// If necessary, it does pre-allocate memory for returned values.
// You can use this file as a starting point for a main function that
// you can deploy in your application.
//
// After you copy the file, and before you deploy it, you must make the
// following changes:
// * For variable-size function arguments, change the example sizes to
// the sizes that your application requires.
// * Change the example values of function arguments to the values that
// your application requires.
// * If the entry-point functions return values, store these values or
// otherwise use them as required by your application.
//
//***********************************************************************
// Include Files
#include "rt_nonfinite.h"
#include "generateMaze.h"
#include "updateMazeTremauxs.h"
#include "updateMazeWallFollower.h"
#include "updateMazePledge.h"
#include "updateMazeRandomMouse.h"
#include "updateMazeShortestPathBFS.h"
#include "updateStartPosition.h"
#include "main.h"
#include "generateMaze_terminate.h"
#include "generateMaze_emxAPI.h"
#include "generateMaze_initialize.h"
#include "eml_rand_mt19937ar_stateful.h"

#include <iostream>
#include <fstream>


// Function Declarations
static void argInit_2x1_real_T(double result[2]);
static void argInit_4x1_real_T(double result[4]);
static void argInit_6x3_real_T(double result[18]);
static double argInit_real_T();
static void argInit_struct0_T(struct0_T *result);
static emxArray_real_T *c_argInit_UnboundedxUnbounded_r();
static void main_generateMaze();
static void main_updateMazeTremauxs();

// Function Definitions

//
// Arguments    : double result[2]
// Return Type  : void
//
static void argInit_2x1_real_T(double result[2])
{
    int idx0;
    
    // Loop over the array to initialize each element.
    for (idx0 = 0; idx0 < 2; idx0++) {
        // Set the value of the array element.
        // Change this value to the value that the application requires.
        result[idx0] = argInit_real_T();
    }
}

//
// Arguments    : double result[4]
// Return Type  : void
//
static void argInit_4x1_real_T(double result[4])
{
    int idx0;
    
    // Loop over the array to initialize each element.
    for (idx0 = 0; idx0 < 4; idx0++) {
        // Set the value of the array element.
        // Change this value to the value that the application requires.
        result[idx0] = argInit_real_T();
    }
}

//
// Arguments    : double result[18]
// Return Type  : void
//
static void argInit_6x3_real_T(double result[18])
{
    int idx0;
    int idx1;
    
    // Loop over the array to initialize each element.
    for (idx0 = 0; idx0 < 6; idx0++) {
        for (idx1 = 0; idx1 < 3; idx1++) {
            // Set the value of the array element.
            // Change this value to the value that the application requires.
            result[idx0 + 6 * idx1] = argInit_real_T();
        }
    }
}

//
// Arguments    : void
// Return Type  : double
//
static double argInit_real_T()
{
    return 0.0;
}

//
// Arguments    : struct0_T *result
// Return Type  : void
//
static void argInit_struct0_T(struct0_T *result)
{
    // Set the value of each structure field.
    // Change this value to the value that the application requires.
    result->grid = c_argInit_UnboundedxUnbounded_r();
    argInit_2x1_real_T(result->exit);
    argInit_4x1_real_T(result->start);
    result->NoWall = argInit_real_T();
    result->Wall = argInit_real_T();
    result->numRows = argInit_real_T();
    result->numCols = argInit_real_T();
    argInit_6x3_real_T(result->colorMap);
    result->BadPath = argInit_real_T();
    result->GoodPath = argInit_real_T();
}

//
// Arguments    : void
// Return Type  : emxArray_real_T *
//
static emxArray_real_T *c_argInit_UnboundedxUnbounded_r()
{
    emxArray_real_T *result;
    static int iv0[2] = { 2, 2 };
    
    int idx0;
    int idx1;
    
    // Set the size of the array.
    // Change this size to the value that the application requires.
    result = emxCreateND_real_T(2, *(int (*)[2])&iv0[0]);
    
    // Loop over the array to initialize each element.
    for (idx0 = 0; idx0 < result->size[0U]; idx0++) {
        for (idx1 = 0; idx1 < result->size[1U]; idx1++) {
            // Set the value of the array element.
            // Change this value to the value that the application requires.
            result->data[idx0 + result->size[0] * idx1] = argInit_real_T();
        }
    }
    
    return result;
}

//
// Arguments    : void
// Return Type  : void
//
static void main_generateMaze()
{
    struct0_T maze;
    emxInit_struct0_T(&maze);
    
    // Initialize function 'generateMaze' input arguments.
    // Call the entry-point 'generateMaze'.
    generateMaze(argInit_real_T(), &maze);
    emxDestroy_struct0_T(maze);
}

//
// Arguments    : void
// Return Type  : void
//
static void main_updateMazeTremauxs()
{
    struct0_T maze;
    boolean_T exitFound;
    
    // Initialize function 'updateMazeTremauxs' input arguments.
    // Initialize function input argument 'maze'.
    argInit_struct0_T(&maze);
    
    // Call the entry-point 'updateMazeTremauxs'.
    exitFound = updateMazeTremauxs(&maze);
    emxDestroy_struct0_T(maze);
}


/*
 * main()
 * This main is a demo for how you can actaully call the update functions
 * to solve the various mazes. In this demo we create 4 different mazes
 * and solve them with the following algorithms
 * - Tremaux's
 * - Shortest Path
 * - Pledge
 * - Wall Follower
 * 
 * We do not show random as it takes a long time to solve.
 */
int main(int argc, const char * const argv[])
{
    // Specify the maze width using the input argument or revert to the
    // default size of 80x80 for the maze.
    double mazeWidth = 80;
    if (argc == 2) {
        mazeWidth = atof(argv[1]);
    }
    
    std::cout<<"In the Main" << std::endl;
    
    // Create a maze structure for each algorithm and initalize them
    struct0_T mazeTremauxs, mazeBFS, mazeWallFollower, mazePledge;
    emxInit_struct0_T(&mazeTremauxs);
    emxInit_struct0_T(&mazeBFS);
    emxInit_struct0_T(&mazeWallFollower);
    emxInit_struct0_T(&mazePledge);
    
    // Initialize the application.
    // You do not need to do this more than one time.
    //generateMaze_initialize();
    rt_InitInfAndNaN(8U);
    startPos_not_empty_init();
    curPos_not_empty_init();
    c_eml_rand_mt19937ar_stateful_i();
    
    // Generate a maze for each of the algorithms.
    std::cout << "Generating  mazes..." << std::endl;
    generateMaze(mazeWidth, &mazeTremauxs);
    generateMaze(mazeWidth, &mazeBFS);
    generateMaze(mazeWidth, &mazeWallFollower);
    generateMaze(mazeWidth, &mazePledge);
    
    // For Tremaux's we demonstrate how to change the start position to be
    // the closest valid position to the 13th row and 13th column
    updateStartPosition(&mazeTremauxs, 13, 13);
    
    std::cout << "Done generating mazes" << std::endl;
    
    // Now solve each maze, one at a time.
    std::ofstream outputFile;
    
    // Tremaux's
    std::cout << "Solving maze using Tremaux's algorithm ..." << std::endl;
    updateMazeTremauxs_init();
    bool exitFound = false;
    while (!exitFound) {
        exitFound = updateMazeTremauxs(&mazeTremauxs);
    }
    
    outputFile.open("outTremaux.txt");
    for (int i = 0; i < mazeWidth*mazeWidth; i++) {
        outputFile << mazeTremauxs.grid->data[i] << " ";
        if(i % (int)mazeWidth == 0) outputFile << '\n';
    }
    outputFile.close();
    updateMazeTremauxs_free();
    
    std::cout << "Created file outTremaux.txt which contains the solved maze" << std::endl;
    
    // Shortest Path BFS
    std::cout << "Solving maze using the shortest path algorithm ..." << std::endl;
    updateMazeShortestPathBFS_init();
    exitFound = false;
    while (!exitFound) {
        exitFound = updateMazeShortestPathBFS(&mazeBFS);
    }
    
    outputFile.open("outBFS.txt");
    for (int i = 0; i < mazeWidth*mazeWidth; i++) {
        outputFile << mazeBFS.grid->data[i] << " ";
        if(i % (int)mazeWidth == 0) outputFile << '\n';
    }
    outputFile.close();
    updateMazeShortestPathBFS_free();
    
    
    std::cout << "Created file outBFS.txt which contains the solved maze" << std::endl;

    // Wall Follower
    std::cout << "Solving maze using the Wall Follower algorithm ..." << std::endl;
    updateMazeWallFollower_init();
    exitFound = false;
    while (!exitFound) {
        exitFound = updateMazeWallFollower(&mazeWallFollower);
    }
    
    outputFile.open("outWallFollower.txt");
    for (int i = 0; i < mazeWidth*mazeWidth; i++) {
        outputFile << mazeWallFollower.grid->data[i] << "\n";
    }
    outputFile.close();
    updateMazeWallFollower_free();
    
    std::cout << "Created file outWallFollower.txt which contains the solved maze" << std::endl;
    
    // Pledge
    std::cout << "Solving maze using the Pledge algorithm ..." << std::endl;
    updateMazePledge_init();
    exitFound = false;
    while (!exitFound) {
        exitFound = updateMazePledge(&mazePledge);
    }
    
    outputFile.open("outPledge.txt");
    for (int i = 0; i < mazeWidth*mazeWidth; i++) {
        outputFile << mazePledge.grid->data[i] << "\n";
    }
    outputFile.close();
    
    std::cout << "Created file outPledge.txt which contains the solved maze" << std::endl;
    
    // Terminate the application.
    // You do not need to do this more than one time.
    generateMaze_terminate();
    emxDestroy_struct0_T(mazeTremauxs);
    emxDestroy_struct0_T(mazeBFS);
    emxDestroy_struct0_T(mazeWallFollower);
    emxDestroy_struct0_T(mazePledge);
    
    return 0;
}

//
// File trailer for main.cpp
//
// [EOF]
//
