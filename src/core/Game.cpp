#include <core/Game.h>
#include <core/PimplImpl.h>
#include <core/Player.h>
#include <core/PlayerTurn.h>
#include <core/Round.h>
#include <core/TurnAction.h>
#include <boost/signals2/signal.hpp>

using namespace edh::core;

struct Game::Impl
{
	boost::signals2::signal<void(std::shared_ptr<Player>)> addPlayerObservers;
	boost::signals2::signal<void(std::shared_ptr<Player>)> removePlayerObservers;
	std::vector<std::shared_ptr<Player>> players{};
	std::vector<std::shared_ptr<Round>> rounds{};
	std::chrono::duration<double> time{};
};

Game::Game()
{
}

Game::~Game()
{
}

void Game::addPlayer(const std::shared_ptr<Player>& x)
{
	this->insertPlayer(this->pimpl->players.size(), x);
}

void Game::insertPlayer(size_t index, const std::shared_ptr<Player>& x)
{
	this->pimpl->players.insert(std::begin(this->pimpl->players) + index, x);
	this->pimpl->addPlayerObservers(x);
}

void Game::removePlayer(const std::shared_ptr<Player>& x)
{
	this->pimpl->removePlayerObservers(x);
	this->pimpl->players.erase(std::remove(std::begin(this->pimpl->players), std::end(this->pimpl->players), x), std::end(this->pimpl->players));
}

int Game::indexOfPlayer(const std::shared_ptr<Player>& x) const
{
	const auto beg = std::begin(this->pimpl->players);
	const auto end = std::end(this->pimpl->players);
	const auto foundIt = std::find(beg, end, x);
	const auto idx = static_cast<int>(foundIt - beg);

	return static_cast<int>(foundIt - beg);
}

std::vector<std::shared_ptr<Player>> Game::getPlayers() const
{
	return this->pimpl->players;
}

void Game::addRound(const std::shared_ptr<Round>& x)
{
	this->pimpl->rounds.push_back(x);
}

std::vector<std::shared_ptr<Round>> Game::getRounds() const
{
	return this->pimpl->rounds;
}

void Game::setTime(std::chrono::duration<double> x)
{
	this->pimpl->time = x;
}

std::chrono::duration<double> Game::getTime() const
{
	return this->pimpl->time;
}

boost::signals2::connection Game::addAddPlayerObserver(const std::function<void(std::shared_ptr<Player>)>& x)
{
	return this->pimpl->addPlayerObservers.connect(x);
}

boost::signals2::connection Game::addRemovePlayerObserver(const std::function<void(std::shared_ptr<Player>)>& x)
{
	return this->pimpl->removePlayerObservers.connect(x);
}
