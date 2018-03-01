#include <core/PlayerTurn.h>

#include <core/Player.h>
#include <core/TurnAction.h>

using namespace edh::core;

PlayerTurn::PlayerTurn(const Player& x) : player{x}
{
}

PlayerTurn::~PlayerTurn()
{
}

const Player& PlayerTurn::getPlayer() const
{
	return this->player;
}

void PlayerTurn::addTurnAction(const TurnAction& x)
{
	this->turnActions.push_back(x);
}

const std::vector<TurnAction>& PlayerTurn::getTurnAction() const
{
	return this->turnActions;
}
