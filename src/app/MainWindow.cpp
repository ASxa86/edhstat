#include <app/MainWindow.h>

#include <core/Game.h>
#include <core/PimplImpl.h>
#include <qt/WidgetPlayers.h>
#include <QtWidgets/QBoxLayout>

using namespace edh;
using namespace edh::core;
using namespace edh::qt;

struct MainWindow::Impl
{
	Game game;
};

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
	this->initializeMenuFile();
	this->initializeMenuEdit();

	auto wPlayers = new WidgetPlayers();
	wPlayers->setGame(&this->pimpl->game);
	this->setCentralWidget(wPlayers);
}

MainWindow::~MainWindow()
{
}

void MainWindow::initializeMenuFile()
{
}

void MainWindow::initializeMenuEdit()
{
}
