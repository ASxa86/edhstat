#include <app/MainWindow.h>

#include <core/Game.h>
#include <core/PimplImpl.h>
#include <core/Player.h>
#include <core/PlayerTurn.h>
#include <core/Round.h>
#include <core/TurnAction.h>
#include <qt/DialogPlayerConfiguration.h>
#include <qt/TreeWidgetRounds.h>
#include <qt/WidgetPlayers.h>
#include <QtCore/QDateTime>
#include <QtCore/QTimer>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>

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
	QTimer timer;

	DialogPlayerConfiguration* dlgPlayerConfig{nullptr};

	std::chrono::high_resolution_clock::time_point time{std::chrono::high_resolution_clock::now()};
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

	auto turnLayout = new QHBoxLayout();
	auto btnNextTurn = new QPushButton("Next Turn");
	turnLayout->addWidget(btnNextTurn);
	turnLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding));
	layout->addLayout(turnLayout);

	auto wRounds = new TreeWidgetRounds();
	wRounds->setGame(this->pimpl->game);
	layout->addWidget(wRounds);

	this->setCentralWidget(centralWidget);

	auto statusBar = new QStatusBar();
	auto lblTime = new QLabel();
	statusBar->addPermanentWidget(lblTime);
	this->setStatusBar(statusBar);

	this->pimpl->timer.setTimerType(Qt::TimerType::PreciseTimer);
	this->pimpl->timer.setInterval(std::chrono::milliseconds(100));

	this->connect(&this->pimpl->timer, &QTimer::timeout, [this, lblTime] {
		const auto time = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - this->pimpl->time);
		this->pimpl->game->setTime(time);
		lblTime->setText(QDateTime::fromTime_t(this->pimpl->game->getTime().count()).toUTC().toString("HH:mm:ss"));

		const auto currentRound = this->pimpl->game->getCurrentRound();

		if(currentRound != nullptr)
		{
			const auto currentTurn = currentRound->getCurrentTurn();

			if(currentTurn != nullptr)
			{
				currentTurn->setTime(time - currentTurn->getStartTime());
				currentTurn->makeDirty();

				const auto currentPlayer = currentTurn->getPlayer();

				if(currentPlayer != nullptr)
				{
					std::chrono::duration<double> playerTime{};

					const auto turns = this->pimpl->game->getTurns(currentPlayer);

					for(const auto& turn : turns)
					{
						playerTime += turn->getTime();
					}

					currentPlayer->setTurnTime(playerTime);
					currentPlayer->makeDirty();
				}
			}
		}
	});

	this->connect(btnNextTurn, &QPushButton::clicked, this, &MainWindow::btnNextTurnClicked);

	this->pimpl->timer.start();
}

MainWindow::~MainWindow()
{
}

void MainWindow::initializeMenuFile()
{
	this->menuBar()->addMenu("File");
}

void MainWindow::initializeMenuEdit()
{
	const auto menuEdit = this->menuBar()->addMenu("Edit");
	const auto menuPreferences = menuEdit->addAction("Preferences");
	this->connect(menuPreferences, &QAction::triggered, [this] {
		const auto dlgPlayerConfig = new DialogPlayerConfiguration(this);
		dlgPlayerConfig->setGame(this->pimpl->game);
		dlgPlayerConfig->setAttribute(Qt::WA_DeleteOnClose);
		dlgPlayerConfig->show();
	});
}

void MainWindow::btnNextTurnClicked()
{
	const auto players = this->pimpl->game->getPlayers();

	auto currentRound = this->pimpl->game->getCurrentRound();

	if(currentRound != nullptr)
	{
		const auto currentTurn = currentRound->getCurrentTurn();

		if(currentTurn != nullptr)
		{
			const auto currentPlayer = currentTurn->getPlayer();
			auto idx = this->pimpl->game->indexOfPlayer(currentPlayer);
			idx++;

			// Check if it is the start of a new round.
			if(idx > static_cast<int>(players.size()) - 1)
			{
				idx = 0;

				currentRound = std::make_shared<Round>();
				this->pimpl->game->addRound(currentRound);
			}

			const auto nextPlayer = players[idx];
			const auto nextTurn = std::make_shared<PlayerTurn>(nextPlayer);
			currentRound->addPlayerTurn(nextTurn);
		}
	}
}
