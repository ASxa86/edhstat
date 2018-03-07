project(EDHQt)

add_library(${PROJECT_NAME} SHARED "")

target_compile_definitions(${PROJECT_NAME} PRIVATE -D${PROJECT_NAME}_Export)

target_sources(${PROJECT_NAME} PRIVATE
	ComboBoxPlayer.h
	ComboBoxTurnActionType.h
	DelegatePlayer.h
	DelegateTurnActionType.h
	DialogPlayerConfiguration.h
	Export.h
	GroupBoxGroup.h
	GroupBoxPlayer.h
	TreeWidgetRounds.h
	WidgetPlayers.h
	WidgetPlayerTable.h
)

target_sources(${PROJECT_NAME} PRIVATE
	ComboBoxPlayer.cpp
	ComboBoxTurnActionType.cpp
	DelegatePlayer.cpp
	DelegateTurnActionType.cpp
	DialogPlayerConfiguration.cpp
	GroupBoxGroup.cpp
	GroupBoxPlayer.cpp
	TreeWidgetRounds.cpp
	WidgetPlayers.cpp
	WidgetPlayerTable.cpp
)


target_link_libraries(${PROJECT_NAME} PUBLIC
	EDHCore
	Qt5::Core
	Qt5::Widgets
	Qt5::Gui
)
