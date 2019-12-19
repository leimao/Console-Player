cmake_minimum_required(VERSION 3.13.0)
project(CPLAYER VERSION 0.1)
set(CMAKE_BUILD_TYPE RelWithDebInfo)
set(CMAKE_CXX_STANDARD 11)

add_library(cplayer STATIC cplayer.cpp cplayer.h)
target_link_libraries(cplayer PRIVATE sndfile asound)

add_executable(console_player main.cpp cplayer.h)
target_link_libraries(console_player PRIVATE cplayer)

