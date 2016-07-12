cmake_minimum_required(VERSION 2.6)
project(mpong)

add_executable(mpong main.cpp server.cpp client.cpp)
set( CMAKE_CXX_FLAGS "-Wall" )
target_link_libraries(mpong SDL2 SDL2_net)
install(TARGETS mpong RUNTIME DESTINATION bin)
