#include <core/Round.h>

#include <core/PlayerTurn.h>
#include <core/TurnAction.h>

using namespace edh::core;

Round::Round()
{
}

Round::~Round()
{
}

void Round::addPlayerTurn(const std::shared_ptr<PlayerTurn>& x)
{
	this->playerTurns.emplace_back(x);
}

std::vector<std::shared_ptr<PlayerTurn>> Round::getPlayerTurns() const
{
	return this->playerTurns;
}
