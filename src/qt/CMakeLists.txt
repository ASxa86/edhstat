####################################################################
#
#	Configure Qt
#

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Widgets Gui)

# On windows, it is possible that Qt is not in the user's path. If not, then copy the necessary binaries
# to the runtime directory.
if(MSVC)
	# Retrieve the binary locations
	get_target_property(qt5core_release Qt5::Core LOCATION)
	get_target_property(qt5widgets_release Qt5::Widgets LOCATION)
	get_target_property(qt5gui_release Qt5::Gui LOCATION)

	# Find the windows platform plugin
	get_target_property(qt5windows Qt5::QWindowsIntegrationPlugin LOCATION)

	# Build a list of release libraries for installation
	set(qt5_binaries
		${qt5core_release}
		${qt5widgets_release}
		${qt5gui_release}
	)

	# Install Qt binaries
	FOREACH(qt5_binary ${qt5_binaries})

		# Rename the release libary to a debug library and then install the debug library
		STRING(REPLACE ".dll" "d.dll" qt5_binary_debug ${qt5_binary})
		FILE(INSTALL ${qt5_binary_debug} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
		FILE(INSTALL ${qt5_binary} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
	endforeach()

	STRING(REPLACE ".dll" "d.dll" qt5windows_debug ${qt5windows})
	FILE(INSTALL ${qt5windows_debug} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/platforms)
	FILE(INSTALL ${qt5windows} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/platforms)
endif()

####################################################################
#
#	Configure EDHQt
#

project(EDHQt)

add_definitions(-D${PROJECT_NAME}_Export)

set(target_h
	Export.h
	Widget.h
)

set(target_src
	Widget.cpp
)

add_library(${PROJECT_NAME} SHARED ${target_h} ${target_src})

add_dependencies(${PROJECT_NAME}
	EDHCore
)

target_link_libraries(${PROJECT_NAME}
	EDHCore
	Qt5::Widgets
	Qt5::Gui
)

install(TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
)
