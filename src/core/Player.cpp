#include <core/Player.h>
#include <core/PimplImpl.h>

using namespace edh::core;

class Player::Impl
{
	public:
		Impl() :
			experienceCounters(0),
			poisonCounters(0),
			lifeTotal(0),
			alive(true)
		{
		}

		std::size_t experienceCounters;
		std::size_t poisonCounters;
		int lifeTotal;
		bool alive;
};

Player::Player(const std::string& id) : Object(id),
	pimpl()
{
}

Player::~Player()
{
}

void Player::setLifeTotal(int x)
{
	this->pimpl->lifeTotal = x;
}

int Player::getLifeTotal() const
{
	return this->pimpl->lifeTotal;
}

void Player::setExperienceCounters(std::size_t x)
{
	this->pimpl->experienceCounters = x;
}

std::size_t Player::getExperienceCounters() const
{
	return this->pimpl->experienceCounters;
}

void Player::setPoisonCounters(std::size_t x)
{
	this->pimpl->poisonCounters = x;
}

std::size_t Player::getPoisonCounters() const
{
	return this->pimpl->poisonCounters;
}

void Player::setAlive(bool x)
{
	this->pimpl->alive = x;
}

bool Player::getAlive() const
{
	return this->pimpl->alive;
}
