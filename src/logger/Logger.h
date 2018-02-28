#pragma once

#include <core/Pimpl.h>
#include <logger/Export.h>
#include <logger/g2log.hpp>

/// Convenience macros for logger. If the internal logger is ever replaced, these
/// macros will remain the same.
#define EDHLogInfo LOG(INFO)
#define EDHLogDebug LOG(DEBUG)
#define EDHLogWarning LOG(WARNING)
#define EDHLogFatal LOG(FATAL)

namespace edh
{
	namespace logger
	{
		///
		///	\class Logger
		///
		///	\brief This class wraps the initilialization of g3log in a nice RAII package.
		///
		///	\date July 30, 2016
		///
		///	\author Aaron Shelley
		///
		class EDHLOGGER_EXPORT Logger
		{
		public:
			Logger(const std::string& prefix, const std::string& directory, bool consoleOutput = true);
			~Logger();

		private:
			class Impl;
			Pimpl<Impl> pimpl;
		};
	}
}
