#########################################################################################
# 
#  Copyright © 2016-2017 Led's Chat All Rights Reserved.
# 
#  These computer program listings and specifications, herein, are
#  the property of Led's Chat and
#  shall not be reproduced or copied or used in whole or in part as
#  the basis for manufacture or sale of items without written permission.
#  Contact: contact@leds-chat.com
#
#
#
#
#########################################################################################

cmake_minimum_required(VERSION 2.8)

set(CMAKE_OSX_DEPLOYMENT_TARGET "10.7" CACHE STRING "Minimum OS X deployment version")

project(Client)

if(WIN32)
    set(EXT ".exe")
elseif(APPLE)
    set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} -stdlib=libc++ -Wall -Wextra -pedantic -std=c++14")
    set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")
    set(EXT "")

    include_directories( /usr/local/include )
    link_directories( /usr/local/lib )
else()

    set(EXT "")
    set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++14")
endif()


find_package (Threads REQUIRED)

set(generatedFolder "${CMAKE_BINARY_DIR}/generated/")

set(generatedJson "${generatedFolder}/mazeJson.h")
set(jsonFile "${CMAKE_SOURCE_DIR}/data/mazes.json")



include_directories (
    include
    .
    ${generatedFolder}
    ${SFML_INCLUDE_DIR}
)

set (
    sourceFiles
    src/main.cxx
    src/squarewave.cxx
    src/redAgent.cxx
    src/greenAgent.cxx
    src/blueAgent.cxx
    src/maze.cxx
    src/utils.cxx
    src/game.cxx
    src/mazeList.cxx

    matlab/all.cpp
    matlab/generateMaze_emxutil.cpp
    matlab/rand.cpp
    matlab/updateMazePledge.cpp
    matlab/any1.cpp
    matlab/generateMaze_initialize.cpp
    matlab/repmat.cpp
    matlab/updateMazeRandomMouse.cpp
    matlab/circshift.cpp
    matlab/generateMaze_rtwutil.cpp
    matlab/rng.cpp
    matlab/updateMazeShortestPathBFS.cpp
    matlab/eml_rand_mt19937ar_stateful.cpp
    matlab/generateMaze_terminate.cpp
    matlab/rtGetInf.cpp
    matlab/updateMazeTremauxs.cpp
    matlab/generateMaze.cpp
    matlab/ifWhileCond.cpp
    matlab/rtGetNaN.cpp
    matlab/updateMazeWallFollower.cpp
    matlab/generateMaze_data.cpp
    matlab/rt_nonfinite.cpp
    matlab/updateStartPosition.cpp
    matlab/generateMaze_emxAPI.cpp
    matlab/mod.cpp
    matlab/sum.cpp
)

set (
    headerFiles

    include/blueAgent.h  
    include/game.h  
    include/greenAgent.h  
    include/mazeAlgorithm.h  
    include/maze.h  
    include/mazeList.h  
    include/redAgent.h  
    include/squarewave.h  
    include/utils.h

    ${generatedJson}
)
                 
add_executable (
    client
    ${sourceFiles}
    ${headerFiles}
)

target_link_libraries(
    client
    ${CMAKE_THREAD_LIBS_INIT}
)


add_custom_command (
    OUTPUT ${generatedJson}
    COMMAND ${CMAKE_COMMAND} -DINPUTFILE=${jsonFile} -DOUTPUTFILE=${generatedJson} -DNAME=mazeJson -P ${CMAKE_SOURCE_DIR}/cmake/fileToHeader.cmake
    DEPENDS ${jsonFile}
)   

add_custom_command (
    TARGET 
    client
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:client> "${CMAKE_SOURCE_DIR}/maze${EXT}"
)
