#include <core/Player.h>

using namespace edh::core;

Player::Player(const std::string& x) : name{x}, lifeTotal{40}, poisonCounters{0}, experienceCounters{0}
{
}

Player::~Player()
{
}

void Player::setName(const std::string& x)
{
	this->name = x;
}

std::string Player::getName() const
{
	return this->name;
}

void Player::setLifeTotal(int x)
{
	this->lifeTotal = x;
}

int Player::getLifeTotal() const
{
	return this->lifeTotal;
}

void Player::setPoisonCounters(int x)
{
	this->poisonCounters = x;
}

int Player::getPoisonCounters() const
{
	return this->poisonCounters;
}

void Player::setExperienceCounters(int x)
{
	this->experienceCounters = x;
}

int Player::getExperienceCounters()
{
	return this->experienceCounters;
}
