cmake_minimum_required(VERSION 3.5)

project(edhstat)

include_directories(${CMAKE_SOURCE_DIR})
set(CMAKE_DEBUG_POSTFIX "d")

# add_subdirectory(app)
add_subdirectory(core)
# add_subdirectory(qt)
