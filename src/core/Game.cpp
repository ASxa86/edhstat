#include <core/Game.h>

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
