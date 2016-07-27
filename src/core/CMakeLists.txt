project(core)

add_definitions(-D${PROJECT_NAME}_export)

set(target_h
	Export.h
	Object.h
)

set(target_src
	Object.cpp
)

add_library(${PROJECT_NAME} SHARED ${target_h} ${target_src})

install(TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
)
