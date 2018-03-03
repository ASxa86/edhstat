#include <qt/WidgetPlayers.h>

#include <core/Game.h>
#include <core/PimplImpl.h>
#include <core/Player.h>
#include <qt/GroupBoxPlayer.h>
#include <QtWidgets/QBoxLayout>

using namespace edh::core;
using namespace edh::qt;

struct WidgetPlayers::Impl
{
	QHBoxLayout* layout{nullptr};
	Game* game{nullptr};
};

WidgetPlayers::WidgetPlayers(QWidget* parent) : QWidget(parent)
{
	this->pimpl->layout = new QHBoxLayout(this);
	this->pimpl->layout->setMargin(0);
}

WidgetPlayers::~WidgetPlayers()
{
}

void WidgetPlayers::setGame(Game* x)
{
	this->pimpl->game = x;

	if(this->pimpl->game != nullptr)
	{
		auto& players = this->pimpl->game->getPlayers();

		for(auto& player : players)
		{
			auto grpPlayer = new GroupBoxPlayer();
			grpPlayer->setPlayer(&player);
			this->pimpl->layout->addWidget(grpPlayer);
		}

		if(players.empty() == true)
		{
			this->pimpl->game->addPlayer(Player("Aaron"));
			this->pimpl->game->addPlayer(Player("Ross"));
			this->pimpl->game->addPlayer(Player("Lee"));
			this->pimpl->game->addPlayer(Player("Jason"));
			this->setGame(this->pimpl->game);
		}
	}
}
