#include <logger/OutputSink.h>
#include <iostream>

#ifdef WIN32
	#include <Windows.h>
#endif

using namespace edh::logger;

OutputSink::OutputSink()
{
}

OutputSink::~OutputSink()
{
	// Ensure the console resets back to white when the logger has finished.
	this->applyColor(INFO);
}

void OutputSink::applyColor(LEVELS level)
{
#ifdef WIN32
	const auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
	if(level == INFO)
	{
		SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
	else if(level == DEBUG)
	{
		SetConsoleTextAttribute(handle, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	}
	else if(level == WARNING)
	{
		SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	}
	else if(level == FATAL)
	{
		SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_INTENSITY);
	}
#else
	if(level == INFO)
	{
		std::cout << "\033[40m\033[37m";
	}
	else if(level == DEBUG)
	{
		std::cout << "\033[40m\033[1;36m";
	}
	else if(level == WARNING)
	{
		std::cout << "\033[40m\033[1;33m";
	}
	else if(level == FATAL)
	{
		std::cout << "\033[40m\033[1;31m";
	}
#endif
}

void OutputSink::onLogMessage(g3::LogMessageMover logEntry)
{
	this->applyColor(logEntry.get()._level);

	std::cout << logEntry.get().message() << "\n";
}
