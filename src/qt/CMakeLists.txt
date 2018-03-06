project(EDHQt)

add_library(${PROJECT_NAME} SHARED "")

target_compile_definitions(${PROJECT_NAME} PRIVATE -D${PROJECT_NAME}_Export)

target_sources(${PROJECT_NAME} PRIVATE
	ComboBoxPlayer.h
	ComboBoxTurnActionType.h
	DelegatePlayer.h
	DelegateTurnActionType.h
	Export.h
	GroupBoxGroup.h
	GroupBoxPlayer.h
	TreeWidgetRounds.h
	WidgetPlayers.h
)

target_sources(${PROJECT_NAME} PRIVATE
	ComboBoxPlayer.cpp
	ComboBoxTurnActionType.cpp
	DelegatePlayer.cpp
	DelegateTurnActionType.cpp
	GroupBoxGroup.cpp
	GroupBoxPlayer.cpp
	TreeWidgetRounds.cpp
	WidgetPlayers.cpp
)


target_link_libraries(${PROJECT_NAME} PUBLIC
	EDHCore
	Qt5::Core
	Qt5::Widgets
	Qt5::Gui
)
