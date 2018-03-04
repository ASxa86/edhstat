#include <core/TurnAction.h>

#include <core/Player.h>

using namespace edh::core;

std::ostream& edh::core::operator<<(std::ostream& os, TurnAction::Type type)
{
	switch(type)
	{
	case TurnAction::Type::CardDraw:
		return os << "Card Draw";
	case TurnAction::Type::LandPlay:
		return os << "Land Play";
	case TurnAction::Type::SpellPlay:
		return os << "Spell Play";
	case TurnAction::Type::LifeGain:
		return os << "Life Gain";
	case TurnAction::Type::LifeLoss:
		return os << "Life Loss";
	}

	return os;
}

std::string edh::core::ToString(TurnAction::Type type)
{
	std::stringstream ss;
	ss << type;
	return ss.str();
}

TurnAction::TurnAction(const std::shared_ptr<Player>& x) : player{x}, target{x}
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

std::shared_ptr<Player> TurnAction::getPlayer() const
{
	return this->player.lock();
}

void TurnAction::setTarget(const std::shared_ptr<Player>& x)
{
	this->target = x;
}

std::shared_ptr<Player> TurnAction::getTarget() const
{
	return this->target.lock();
}
