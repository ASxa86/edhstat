#include <core/Game.h>
#include <core/Player.h>
#include <core/PlayerTurn.h>
#include <core/Round.h>
#include <core/TurnAction.h>

using namespace edh::core;

Game::Game()
{
}

Game::~Game()
{
}

void Game::addPlayer(const std::shared_ptr<Player>& x)
{
	this->players.push_back(x);
}

std::vector<std::shared_ptr<Player>> Game::getPlayers() const
{
	return this->players;
}

void Game::addRound(const std::shared_ptr<Round>& x)
{
	this->rounds.push_back(x);
}

std::vector<std::shared_ptr<Round>> Game::getRounds() const
{
	return this->rounds;
}

void Game::setTime(std::chrono::duration<double> x)
{
	this->time = x;
}

std::chrono::duration<double> Game::getTime() const
{
	return this->time;
}
