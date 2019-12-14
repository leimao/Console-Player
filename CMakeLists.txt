cmake_minimum_required(VERSION 3.0.0)

project(SNAKE VERSION 0.0.1)

set(CMAKE_BUILD_TYPE Debug)


set (CMAKE_CXX_STANDARD 11)

add_executable(main main.cpp cplayer.cpp)
target_link_libraries(main PRIVATE sndfile asound)