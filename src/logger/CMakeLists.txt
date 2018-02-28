add_library(EDHLogger SHARED "")

target_compile_definitions(EDHLogger PRIVATE -DEDHLogger_Export)

target_sources(EDHLogger
	PRIVATE
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

	PUBLIC
		Export.h
		Logger.h
		OutputSink.h
)

target_sources(EDHLogger
	PRIVATE
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
	target_sources(EDHLogger
		PRIVATE
			g3log/stacktrace_windows.hpp
			crashhandler_windows.cpp
			stacktrace_windows.cpp
	)
else()
	target_sources(EDHLogger
		PRIVATE
			crashhandler_unix.cpp
	)
endif()
