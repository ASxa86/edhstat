#include <core/PlayerTurn.h>

#include <core/Player.h>
#include <core/TurnAction.h>

using namespace edh::core;

PlayerTurn::PlayerTurn(const std::shared_ptr<Player>& x) : player{x}, startTime{}, time{}
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

std::vector<std::shared_ptr<TurnAction>> PlayerTurn::getTurnActions() const
{
	return this->turnActions;
}

void PlayerTurn::setStartTime(std::chrono::duration<double> x)
{
	this->startTime = x;
}

std::chrono::duration<double> PlayerTurn::getStartTime() const
{
	return this->startTime;
}

void PlayerTurn::setTime(std::chrono::duration<double> x)
{
	this->time = x;
}

std::chrono::duration<double> PlayerTurn::getTime() const
{
	return this->time;
}
