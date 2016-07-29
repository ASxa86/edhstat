#include <core/Turn.h>
#include <core/PimplImpl.h>

using namespace edh::core;

class Turn::Impl
{
	public:
		Impl() :
			poisonCounterDelta(0),
			experienceCounterDelta(0),
			time(0.0),
			lifeTotalDelta(0)
		{
		}

		std::size_t poisonCounterDelta;
		std::size_t experienceCounterDelta;
		double time;
		int lifeTotalDelta;

};

Turn::Turn(const std::string& id) : Object(id),
	pimpl()
{
}

Turn::~Turn()
{
}

void Turn::setTime(double x)
{
	this->pimpl->time = x;
}

double Turn::getTime() const
{
	return this->pimpl->time;
}

void Turn::setLifeTotalDelta(int x)
{
	this->pimpl->lifeTotalDelta = x;
}

int Turn::getLifeTotalDelta() const
{
	return this->pimpl->lifeTotalDelta;
}

void Turn::setPoisonCounterDelta(std::size_t x)
{
	this->pimpl->poisonCounterDelta = x;
}

std::size_t Turn::getPoisonCounterDelta() const
{
	return this->pimpl->poisonCounterDelta;
}

void Turn::setExperienceCounterDelta(std::size_t x)
{
	this->pimpl->experienceCounterDelta = x;
}

std::size_t Turn::getExperienceCounterDelta() const
{
	return this->pimpl->experienceCounterDelta;
}
