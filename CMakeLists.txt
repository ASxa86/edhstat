cmake_minimum_required(VERSION 3.5)

project(edhstat)

if(MSVC) 
	add_compile_options(/wd4251) # w4251 - 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
	add_compile_options(/W4)
	add_compile_options(/MP)
	add_compile_options(/WX)
	add_compile_options(/D_SCL_SECURE_NO_WARNINGS)
	add_compile_options(/permissive-)
	add_compile_options(-std:c++17)
elseif(CMAKE_COMPILER_IS_GNUCXX) 
	add_definitions("-Werror")
elseif(CMAKE_COMPILER_IS_GNUCC)
	add_definitions("-Werror")
endif()

set(CMAKE_DEBUG_POSTFIX          "d" CACHE STRING "add a postfix, usually d on windows")
set(CMAKE_RELEASE_POSTFIX        "" CACHE STRING "add a postfix, usually empty on windows")
set(CMAKE_RELWITHDEBINFO_POSTFIX "rd" CACHE STRING "add a postfix, usually empty on windows")
set(CMAKE_MINSIZEREL_POSTFIX     "s" CACHE STRING "add a postfix, usually empty on windows")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

include_directories(${CMAKE_SOURCE_DIR}/src)

#####################################################
#
#	Find Qt5
#

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Core Gui Widgets)

add_subdirectory(src)
