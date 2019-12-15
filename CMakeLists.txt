cmake_minimum_required(VERSION 3.0.0)
project(CONSOLE_SOUND_PLAYER VERSION 0.0.1)
set(CMAKE_BUILD_TYPE RelWithDebInfo)
set (CMAKE_CXX_STANDARD 11)

#SET(CMAKE_INSTALL_PREFIX .)

add_subdirectory(src)
add_subdirectory(bgm)

install(FILES src/cplayer.h DESTINATION include)
install(TARGETS cplayer LIBRARY DESTINATION lib) 
install(TARGETS console_player RUNTIME DESTINATION bin) 
install(TARGETS bgm RUNTIME DESTINATION bin) 
