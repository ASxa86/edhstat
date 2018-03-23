#include <qt/WidgetPlayers.h>

#include <core/Game.h>
#include <core/PimplImpl.h>
#include <core/Player.h>
#include <core/signal.h>
#include <qt/GroupBoxGroup.h>
#include <qt/GroupBoxPlayer.h>
#include <QtWidgets/QBoxLayout>
#include <boost/signals2/connection.hpp>

using namespace edh::core;
using namespace edh::qt;

struct WidgetPlayers::Impl
{
	std::vector<boost::signals2::scoped_connection> connections;
	QHBoxLayout* layout{nullptr};
	GroupBoxGroup* group{nullptr};
	std::weak_ptr<Game> game{};
};

WidgetPlayers::WidgetPlayers(QWidget* parent) : QWidget(parent)
{
	this->pimpl->layout = new QHBoxLayout(this);
	this->pimpl->layout->setMargin(0);

	this->pimpl->group = new GroupBoxGroup(this);
}

WidgetPlayers::~WidgetPlayers()
{
}

void WidgetPlayers::setGame(const std::shared_ptr<Game>& x)
{
	this->clear();
	this->pimpl->game = x;

	if(x != nullptr)
	{
		auto players = x->getPlayers();

		for(const auto& player : players)
		{
			auto grpPlayer = new GroupBoxPlayer();
			grpPlayer->setPlayer(player);
			this->pimpl->group->addGroupBox(grpPlayer);
			this->pimpl->layout->addWidget(grpPlayer);
		}

		this->pimpl->layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding));

		this->pimpl->connections.push_back(x->addAddPlayerObserver([this](std::shared_ptr<Player> x) {
			const auto game = this->pimpl->game.lock();

			if(game != nullptr)
			{
				auto grpPlayer = new GroupBoxPlayer();
				grpPlayer->setPlayer(x);
				this->pimpl->group->addGroupBox(grpPlayer);
				this->pimpl->layout->insertWidget(game->indexOfPlayer(x), grpPlayer);
			}
		}));

		this->pimpl->connections.push_back(x->addRemovePlayerObserver([this](std::shared_ptr<Player> x) {
			const auto widgets = this->findChildren<QWidget*>();

			for(const auto& widget : widgets)
			{
				const auto grpPlayer = dynamic_cast<GroupBoxPlayer*>(widget);

				if(grpPlayer != nullptr)
				{
					if(grpPlayer->getPlayer() == x)
					{
						delete grpPlayer;
						break;
					}
				}
			}
		}));
	}
}

void WidgetPlayers::clear()
{
	const auto children = this->findChildren<QWidget*>();

	for(const auto& child : children)
	{
		delete child;
	}
}
