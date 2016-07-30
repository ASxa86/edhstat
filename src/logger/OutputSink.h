#pragma once

#include <logger/g2log.hpp>

namespace edh
{
	namespace logger
	{
		///
		///	\class OutputSink
		///
		///	\brief This is a console output sink for g3log.
		///
		///	\date July 30, 2016
		///
		///	\author Aaron Shelley
		///
		class OutputSink
		{
			public:
				OutputSink();
				~OutputSink();

				void applyColor(LEVELS level);
				void onLogMessage(g3::LogMessageMover logEntry);
		};
	}
}
