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

boost::signals2::connection Player::addDirtyObserver(const std::function<void(std::shared_ptr<Player>)>& x)
{
	return this->pimpl->dirtyObservers.connect(x);
}

void Player::makeDirty()
{
	this->pimpl->dirtyObservers(this->shared_from_this());
}
