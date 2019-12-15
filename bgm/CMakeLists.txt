cmake_minimum_required(VERSION 3.0.0)
project(CPLAYER VERSION 0.1)
set(CMAKE_BUILD_TYPE RelWithDebInfo)
set(CMAKE_CXX_STANDARD 11)

include_directories(../src)

add_executable(bgm bgm.cpp)
target_link_libraries(bgm PRIVATE cplayer pthread)
