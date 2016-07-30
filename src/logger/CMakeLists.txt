project(EDHLogger)

add_definitions(-D${PROJECT_NAME}_Export)

set(target_h
	g3log/time.hpp
	g3log/active.hpp
	g3log/crashhandler.hpp
	g3log/filesink.hpp
	g3log/future.hpp
	g3log/g3log.hpp
	g3log/generated_definitions.hpp
	g3log/logcapture.hpp
	g3log/loglevels.hpp
	g3log/logmessage.hpp
	g3log/logworker.hpp
	g3log/moveoncopy.hpp
	g3log/shared_queue.hpp
	g3log/sink.hpp
	g3log/sinkhandle.hpp
	g3log/sinkwrapper.hpp
	g3log/std2_make_unique.hpp
	g3log/stlpatch_future.hpp
	Export.h
	Logger.h
	OutputSink.h
)

set(target_src
	g3log.cpp
	logcapture.cpp
	loglevels.cpp
	logmessage.cpp
	logworker.cpp
	time.cpp
	filesink.cpp
	filesinkhelper.ipp
	g2log.hpp
	Logger.cpp
	OutputSink.cpp
)

if(MSVC)
	list(APPEND target_h
		g3log/stacktrace_windows.hpp
	)

	list(APPEND target_src
		crashhandler_windows.cpp
		stacktrace_windows.cpp
	)
else()
	list(APPEND target_src
		crashhandler_unix.cpp
	)
endif()

if(MSVC)
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

add_library(${PROJECT_NAME} SHARED ${target_h} ${target_src})

install(TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
)
