add_library(EDHCore SHARED "")

target_compile_definitions(EDHCore PRIVATE -DEDHCore_Export)

target_sources(EDHCore
	PRIVATE
		Export.h
		Game.h
		Player.h
		Pimpl.h
		PimplImpl.h
)

target_sources(EDHCore
	PRIVATE
		Game.cpp
		Player.cpp
)
