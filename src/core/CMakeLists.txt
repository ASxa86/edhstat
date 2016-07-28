project(EDHCore)

add_definitions(-D${PROJECT_NAME}_Export)

set(target_h
	config.hpp
	connection.hpp
	connections.hpp
	Export.h
	Object.h
	Pimpl.h
	PimplImpl.h
	signal.hpp
	signals.hpp
)

set(target_src
	Object.cpp
)

add_library(${PROJECT_NAME} SHARED ${target_h} ${target_src})

install(TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
)
