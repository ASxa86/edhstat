#pragma once

#ifdef WIN32
	#ifdef EDHLogger_Export
		#define EDHLOGGER_EXPORT _declspec(dllexport)
	#else
		#define EDHLOGGER_EXPORT _declspec(dllimport)
	#endif
#else
	#define EDHLOGGER_EXPORT
#endif
