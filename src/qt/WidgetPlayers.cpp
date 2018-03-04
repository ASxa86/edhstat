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
	std::weak_ptr<Game> game{};
};

WidgetPlayers::WidgetPlayers(QWidget* parent) : QWidget(parent)
{
	this->pimpl->layout = new QHBoxLayout(this);
	this->pimpl->layout->setMargin(0);
}

WidgetPlayers::~WidgetPlayers()
{
}

void WidgetPlayers::setGame(const std::shared_ptr<Game>& x)
{
	this->pimpl->game = x;

	if(x != nullptr)
	{
		auto players = x->getPlayers();

		for(const auto& player : players)
		{
			auto grpPlayer = new GroupBoxPlayer();
			grpPlayer->setPlayer(player);
			this->pimpl->layout->addWidget(grpPlayer);
		}
	}
}
