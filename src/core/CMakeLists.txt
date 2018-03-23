project(EDHCore)

add_library(${PROJECT_NAME} SHARED "")

target_compile_definitions(${PROJECT_NAME} PRIVATE -D${PROJECT_NAME}_Export)
target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIR})

target_sources(${PROJECT_NAME} PRIVATE
	Export.h
	Game.h
	Pimpl.h
	PimplImpl.h
	Player.h
	PlayerTurn.h
	Round.h
	TurnAction.h
)

target_sources(${PROJECT_NAME} PRIVATE
	Game.cpp
	Player.cpp
	PlayerTurn.cpp
	Round.cpp
	TurnAction.cpp
)
