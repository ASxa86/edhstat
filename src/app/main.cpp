#include <app/MainWindow.h>
#include <QtWidgets/QApplication>

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	edh::MainWindow window;
	window.resize(1280, 720);
	window.show();
	return app.exec();;
}
