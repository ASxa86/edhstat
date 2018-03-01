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

void Game::addPlayer(const Player& x)
{
	this->players.push_back(x);
}

const std::vector<Player>& Game::getPlayers() const
{
	return this->players;
}

void Game::addRound(const Round& x)
{
	this->rounds.push_back(x);
}

const std::vector<Round>& Game::getRounds() const
{
	return this->rounds;
}
