#pragma once

#ifdef WIN32
	#ifdef EDHCore_Export
		#define EDHCORE_EXPORT _declspec(dllexport)
	#else
		#define EDHCORE_EXPORT _declspec(dllimport)
	#endif
#else
	#define EDHCORE_EXPORT
#endif
