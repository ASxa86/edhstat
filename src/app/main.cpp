#include <app/FormMain.h>
#include <QtWidgets/QApplication>

#include <logger/Logger.h>

// Remove the console window if running on windows in release.
#if defined(WIN32) && !defined(_DEBUG)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

int main(int argc, char** argv)
{
	// In release, there is no need for a logger as a console window will not be provided.
	auto consoleOutput = true;
#ifndef _DEBUG
	consoleOutput = false;
#endif

	edh::logger::Logger logger("edhstat", ".", consoleOutput);

	QApplication app(argc, argv);
	edh::FormMain frmMain;
	frmMain.show();

	return app.exec();
}
