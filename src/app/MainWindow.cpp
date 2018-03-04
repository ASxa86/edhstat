#include <app/MainWindow.h>

#include <core/Game.h>
#include <core/Player.h>
#include <core/PlayerTurn.h>
#include <core/Round.h>
#include <core/TurnAction.h>
#include <core/PimplImpl.h>
#include <qt/TreeWidgetRounds.h>
#include <qt/WidgetPlayers.h>
#include <QtWidgets/QBoxLayout>

using namespace edh;
using namespace edh::core;
using namespace edh::qt;

struct MainWindow::Impl
{
	Impl()
	{
		const auto aaron = std::make_shared<Player>("Aaron");
		this->game->addPlayer(aaron);
		this->game->addPlayer(std::make_shared<Player>("Ross"));
		this->game->addPlayer(std::make_shared<Player>("Lee"));
		this->game->addPlayer(std::make_shared<Player>("Jason"));

		const auto round = std::make_shared<Round>();
		const auto aaronTurn = std::make_shared<PlayerTurn>(aaron);

		const auto action = std::make_shared<TurnAction>(aaron);
		action->setType(TurnAction::Type::CardDraw);
		action->setCount(1);
		aaronTurn->addTurnAction(action);

		round->addPlayerTurn(aaronTurn);
		this->game->addRound(round);
	}

	std::shared_ptr<Game> game{std::make_shared<Game>()};
};

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
	this->initializeMenuFile();
	this->initializeMenuEdit();

	auto centralWidget = new QWidget();
	auto layout = new QVBoxLayout(centralWidget);
	layout->setMargin(0);

	auto wPlayers = new WidgetPlayers();
	wPlayers->setGame(this->pimpl->game);
	layout->addWidget(wPlayers);

	auto wRounds = new TreeWidgetRounds();
	wRounds->setGame(this->pimpl->game);
	layout->addWidget(wRounds);

	this->setCentralWidget(centralWidget);
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
