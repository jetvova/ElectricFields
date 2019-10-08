cmake_minimum_required(VERSION 3.13)
project(experiments)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)

add_executable(experiments main.cpp ChargedParticle.cpp ChargedParticle.h Utils.cpp Utils.h)
target_link_libraries(experiments ${SDL2_LIBRARIES})
