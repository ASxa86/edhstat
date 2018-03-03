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

std::vector<Player>& Game::getPlayers()
{
	return this->players;
}

void Game::addRound(const Round& x)
{
	this->rounds.push_back(x);
}

std::vector<Round>& Game::getRounds()
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
