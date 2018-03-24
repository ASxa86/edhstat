#include <core/Round.h>

#include <core/Game.h>
#include <core/PlayerTurn.h>
#include <core/TurnAction.h>
#include <core/PimplImpl.h>
#include <boost/signals2/signal.hpp>

using namespace edh::core;

struct Round::Impl
{
	boost::signals2::signal<void(std::shared_ptr<PlayerTurn>)> addTurnObservers;
	std::vector<std::shared_ptr<PlayerTurn>> playerTurns;
	std::weak_ptr<Game> game;
};

Round::Round()
{
}

Round::~Round()
{
}

void Round::addPlayerTurn(const std::shared_ptr<PlayerTurn>& x)
{
	this->pimpl->playerTurns.emplace_back(x);

	const auto g = this->getGame();

	if(g != nullptr)
	{
		x->setStartTime(g->getTime());
	}

	this->pimpl->addTurnObservers(x);
}

std::shared_ptr<PlayerTurn> Round::getCurrentTurn() const
{
	if(this->pimpl->playerTurns.empty() == false)
	{
		return this->pimpl->playerTurns.back();
	}

	return nullptr;
}

std::vector<std::shared_ptr<PlayerTurn>> Round::getPlayerTurns() const
{
	return this->pimpl->playerTurns;
}

void Round::setGame(const std::shared_ptr<Game>& x)
{
	this->pimpl->game = x;
}

std::shared_ptr<Game> Round::getGame() const
{
	return this->pimpl->game.lock();
}

boost::signals2::connection Round::addAddTurnObserver(const std::function<void(std::shared_ptr<PlayerTurn>)>& x)
{
	return this->pimpl->addTurnObservers.connect(x);
}
