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
    set(EXT "")
    set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} -stdlib=libc++ -Wall -Wextra -pedantic -std=c++14")
    set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")
    
else()
    set(EXT "")
    set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++14")
endif()


find_package (Threads REQUIRED)

include_directories (
    include
    lib
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

    lib/matlab/all.cpp
    lib/matlab/generateMaze_emxutil.cpp
    lib/matlab/rand.cpp
    lib/matlab/updateMazePledge.cpp
    lib/matlab/any1.cpp
    lib/matlab/generateMaze_initialize.cpp
    lib/matlab/repmat.cpp
    lib/matlab/updateMazeRandomMouse.cpp
    lib/matlab/circshift.cpp
    lib/matlab/generateMaze_rtwutil.cpp
    lib/matlab/rng.cpp
    lib/matlab/updateMazeShortestPathBFS.cpp
    lib/matlab/eml_rand_mt19937ar_stateful.cpp
    lib/matlab/generateMaze_terminate.cpp
    lib/matlab/rtGetInf.cpp
    lib/matlab/updateMazeTremauxs.cpp
    lib/matlab/generateMaze.cpp
    lib/matlab/ifWhileCond.cpp
    lib/matlab/rtGetNaN.cpp
    lib/matlab/updateMazeWallFollower.cpp
    lib/matlab/generateMaze_data.cpp
    lib/matlab/rt_nonfinite.cpp
    lib/matlab/updateStartPosition.cpp
    lib/matlab/generateMaze_emxAPI.cpp
    lib/matlab/mod.cpp
    lib/matlab/sum.cpp
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
    TARGET 
    client
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:client> "${CMAKE_SOURCE_DIR}/maze${EXT}"
)
