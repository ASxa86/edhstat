#include <core/TurnAction.h>

#include <core/Player.h>

using namespace edh::core;

TurnAction::TurnAction(const Player& x) : player{x}, target{x}
{
}

TurnAction::~TurnAction()
{
}

void TurnAction::setType(TurnAction::Type x)
{
	this->type = x;
}

TurnAction::Type TurnAction::getType() const
{
	return this->type;
}

void TurnAction::setCount(int x)
{
	this->count = x;
}

int TurnAction::getCount() const
{
	return this->count;
}

const Player& TurnAction::getPlayer() const
{
	return this->player;
}

void TurnAction::setTarget(const Player& x)
{
	this->target = x;
}

const Player& TurnAction::getTarget() const
{
	return this->target;
}
