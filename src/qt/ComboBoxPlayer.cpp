#include <qt/ComboBoxPlayer.h>

#include <core/Game.h>
#include <core/PimplImpl.h>
#include <core/Player.h>

using namespace edh::core;
using namespace edh::qt;

Q_DECLARE_METATYPE(std::weak_ptr<edh::core::Player>)

struct ComboBoxPlayer::Impl
{
	std::weak_ptr<Game> game;
};

ComboBoxPlayer::ComboBoxPlayer(QWidget* parent) : QComboBox(parent)
{
	qRegisterMetaType<std::weak_ptr<edh::core::Player>>();
}

ComboBoxPlayer::~ComboBoxPlayer()
{
}

void ComboBoxPlayer::setGame(const std::shared_ptr<Game>& x)
{
	this->pimpl->game = x;

	if(x != nullptr)
	{
		const auto players = x->getPlayers();

		for(const auto& player : players)
		{
			std::weak_ptr<Player> weakPlayer = player;
			this->addItem(QString::fromStdString(player->getName()), QVariant::fromValue(weakPlayer));
		}
	}
}

void ComboBoxPlayer::setCurrentPlayer(const std::shared_ptr<Player>& x)
{
	for(auto i = 0; i < this->count(); i++)
	{
		auto player = this->itemData(i).value<std::weak_ptr<Player>>().lock();

		if(player == x)
		{
			this->setCurrentIndex(i);
			break;
		}
	}
}

std::shared_ptr<Player> ComboBoxPlayer::getCurrentPlayer() const
{
	return this->currentData().value<std::weak_ptr<Player>>().lock();
}
