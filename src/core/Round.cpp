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

void Round::addPlayerTurn(const PlayerTurn& x)
{
	this->playerTurns.emplace_back(std::move(x));
}

const std::vector<PlayerTurn>& Round::getPlayerTurns() const
{
	return this->playerTurns;
}
