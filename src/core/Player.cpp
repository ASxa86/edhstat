#include <core/Player.h>

#include <core/PimplImpl.h>
#include <boost/signals2/signal.hpp>

using namespace edh::core;

struct Player::Impl
{
	Impl(const std::string& x) : name{x}
	{
	}

	boost::signals2::signal<void(std::shared_ptr<Player>)> dirtyObservers{};
	std::string name{};
	std::chrono::duration<double> turnTime{0.0};
	int lifeTotal{40};
	int poisonCounters{0};
	int experienceCounters{0};
};

Player::Player(const std::string& x) : pimpl{x}
{
}

Player::~Player()
{
}

void Player::setName(const std::string& x)
{
	this->pimpl->name = x;
}

std::string Player::getName() const
{
	return this->pimpl->name;
}

void Player::setLifeTotal(int x)
{
	this->pimpl->lifeTotal = x;
}

int Player::getLifeTotal() const
{
	return this->pimpl->lifeTotal;
}

void Player::setPoisonCounters(int x)
{
	this->pimpl->poisonCounters = x;
}

int Player::getPoisonCounters() const
{
	return this->pimpl->poisonCounters;
}

void Player::setExperienceCounters(int x)
{
	this->pimpl->experienceCounters = x;
}

int Player::getExperienceCounters()
{
	return this->pimpl->experienceCounters;
}

void Player::setTurnTime(std::chrono::duration<double> x)
{
	this->pimpl->turnTime = x;
}

std::chrono::duration<double> Player::getTurnTime() const
{
	return this->pimpl->turnTime;
}
