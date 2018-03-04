#include <core/PlayerTurn.h>

#include <core/Player.h>
#include <core/TurnAction.h>

using namespace edh::core;

PlayerTurn::PlayerTurn(const std::shared_ptr<Player>& x) : player{x}
{
}

PlayerTurn::~PlayerTurn()
{
}

std::shared_ptr<Player> PlayerTurn::getPlayer() const
{
	return this->player.lock();
}

void PlayerTurn::addTurnAction(const std::shared_ptr<TurnAction>& x)
{
	this->turnActions.push_back(x);
}

std::vector<std::shared_ptr<TurnAction>> PlayerTurn::getTurnAction() const
{
	return this->turnActions;
}

void PlayerTurn::setTime(std::chrono::duration<double> x)
{
	this->time = x;
}

std::chrono::duration<double> PlayerTurn::getTime() const
{
	return this->time;
}
