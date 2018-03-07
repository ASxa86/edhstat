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

std::shared_ptr<PlayerTurn> Round::getCurrentTurn() const
{
	if(this->playerTurns.empty() == false)
	{
		return this->playerTurns.back();
	}

	return nullptr;
}

std::vector<std::shared_ptr<PlayerTurn>> Round::getPlayerTurns() const
{
	return this->playerTurns;
}
