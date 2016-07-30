#include <logger/Logger.h>
#include <core/PimplImpl.h>

#include <logger/OutputSink.h>

using namespace edh::logger;

class Logger::Impl
{
	public:
		Impl(const std::string& p, const std::string& d, bool consoleOutput)
		{
			this->worker = g3::LogWorker::createLogWorker();
			this->fileLogger = this->worker->addDefaultLogger(p, d, "");

			if(consoleOutput == true)
			{
				this->consoleOutput = this->worker->addSink(std::make_unique<OutputSink>(), &OutputSink::onLogMessage);
			}

			g3::initializeLogging(this->worker.get());
		}

		std::unique_ptr<g3::LogWorker> worker;
		std::unique_ptr<g3::FileSinkHandle> fileLogger;
		std::unique_ptr<g3::SinkHandle<OutputSink>> consoleOutput;
};

Logger::Logger(const std::string& prefix, const std::string& directory, bool consoleOutput) :
	pimpl(prefix, directory, consoleOutput)
{
}

Logger::~Logger()
{
}
