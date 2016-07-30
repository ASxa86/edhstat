cmake_minimum_required(VERSION 3.5)

project(edhstat)

include_directories(${CMAKE_SOURCE_DIR})
set(CMAKE_DEBUG_POSTFIX "d")

# Disable dll interface warning caused by the use of std::unique_ptr as a private member variable for PIMPL.
add_definitions(/wd4251)

# warning C4091: 'typedef ': ignored on left of '' when no variable is declared
# This is a bug for the Windows 10 platform found in dbghelp.h
add_definitions(/wd4091)

add_subdirectory(app)
add_subdirectory(core)
add_subdirectory(logger)
add_subdirectory(qt)
