####################################################################
#
#	Configure Qt
#

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Widgets Gui)

####################################################################
#
#	Configure EDHStat
#

project(EDHStat)

set(target_h
	FormMain.h
)

set(target_src
	FormMain.cpp
	main.cpp
)

add_executable(${PROJECT_NAME} ${target_h} ${target_src})
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

add_dependencies(${PROJECT_NAME}
	EDHQt
)

target_link_libraries(${PROJECT_NAME} EDHQt)

install(TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
)
