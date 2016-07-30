project(EDHCore)

add_definitions(-D${PROJECT_NAME}_Export)

set(target_h
	config.hpp
	connection.hpp
	connections.hpp
	Export.h
	Game.h
	Object.h
	Pimpl.h
	PimplImpl.h
	Player.h
	Rules.h
	signal.hpp
	signals.hpp
	Turn.h
)

set(target_src
	Game.cpp
	Object.cpp
	Player.cpp
	Rules.cpp
	Turn.cpp
)

add_library(${PROJECT_NAME} SHARED ${target_h} ${target_src})

add_dependencies(${PROJECT_NAME}
	EDHLogger
)

target_link_libraries(${PROJECT_NAME}
	EDHLogger
)

install(TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
)
