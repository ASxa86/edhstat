project(edhstat)

add_executable(${PROJECT_NAME} "")

target_sources(${PROJECT_NAME} PRIVATE
	MainWindow.h
)

target_sources(${PROJECT_NAME} PRIVATE
	main.cpp
	MainWindow.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	EDHQt
)
