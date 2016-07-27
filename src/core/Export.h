#pragma once

#ifdef WIN32
	#ifdef core_export
		#define CORE_EXPORT _declspec(dllexport)
	#else
		#define CORE_EXPORT _declspec(dllimport)
	#endif
#else
	#define CORE_EXPORT
#endif
