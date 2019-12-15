cmake_minimum_required(VERSION 3.0.0)

project(CPLAYER VERSION 0.0.1)

set(CMAKE_BUILD_TYPE RelWithDebInfo)
#set(CMAKE_BUILD_TYPE Release)

set (CMAKE_CXX_STANDARD 11)

set(CMAKE_BUILD_TYPE RelWithDebInfo)

add_library(cplayer STATIC cplayer.cpp cplayer.h)
target_link_libraries(cplayer PRIVATE sndfile asound)

add_executable(main main.cpp cplayer.h)
target_link_libraries(main PRIVATE cplayer)

add_executable(bgm bgm.cpp)
target_link_libraries(bgm PRIVATE cplayer pthread)

#install(TARGETS cplayer
#        CONFIGURATIONS Release
#        RUNTIME DESTINATION lib)

#install(TARGETS main
#        CONFIGURATIONS Release
#        RUNTIME DESTINATION bin)
