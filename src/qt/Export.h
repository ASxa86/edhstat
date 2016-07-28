#pragma once

#ifdef WIN32
	#ifdef EDHQt_Export
		#define EDHQT_EXPORT _declspec(dllexport)
	#else
		#define EDHQT_EXPORT _declspec(dllimport)
	#endif
#else
	#define EDHQT_EXPORT
#endif
