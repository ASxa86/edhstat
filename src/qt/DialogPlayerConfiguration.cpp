#include <qt/DialogPlayerConfiguration.h>

#include <core/Game.h>
#include <core/PimplImpl.h>
#include <core/Player.h>
#include <qt/TableWidgetPlayer.h>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QPushButton>

using namespace edh::core;
using namespace edh::qt;

struct DialogPlayerConfiguration::Impl
{
	std::weak_ptr<Game> game;

	TableWidgetPlayer* wPlayerTable{new TableWidgetPlayer()};
};

DialogPlayerConfiguration::DialogPlayerConfiguration(QWidget* parent) : QDialog(parent), pimpl()
{
	const auto layout = new QVBoxLayout(this);
	layout->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);

	const auto buttonLayout = new QHBoxLayout();
	const auto btnPlayerAdd = new QPushButton("Add Player");
	const auto btnPlayerRemove = new QPushButton("Remove Player");
	buttonLayout->addWidget(btnPlayerAdd);
	buttonLayout->addWidget(btnPlayerRemove);
	buttonLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding));
	layout->addLayout(buttonLayout);

	layout->addWidget(this->pimpl->wPlayerTable);

	this->connect(btnPlayerAdd, &QPushButton::clicked, [this] {
		const auto game = this->pimpl->game.lock();

		if(game != nullptr)
		{
			auto player = std::make_shared<Player>("Name");
			game->addPlayer(player);
		}
	});

	this->connect(btnPlayerRemove, &QPushButton::clicked, [this] {
		const auto player = this->pimpl->wPlayerTable->getCurrentPlayer();

		if(player != nullptr)
		{
			const auto game = this->pimpl->game.lock();

			if(game != nullptr)
			{
				game->removePlayer(player);
			}
		}
	});
}

DialogPlayerConfiguration::~DialogPlayerConfiguration()
{
}

void DialogPlayerConfiguration::setGame(const std::shared_ptr<edh::core::Game>& x)
{
	this->pimpl->game = x;

	if(x != nullptr)
	{
		this->pimpl->wPlayerTable->setGame(x);
	}
}
