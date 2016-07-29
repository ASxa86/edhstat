#include <core/Rules.h>
#include <core/PimplImpl.h>

using namespace edh::core;

class Rules::Impl
{
	public:
		Impl() :
			poisonCounterLimit(10),
			startingLifeTotal(40)
		{
		}

		std::size_t poisonCounterLimit;
		int startingLifeTotal;
};

Rules::Rules(const std::string& id) : Object(id),
	pimpl()
{
}

Rules::~Rules()
{
}

void Rules::setStartingLifeTotal(int x)
{
	this->pimpl->startingLifeTotal = x;
}

int Rules::getStartingLifeTotal() const
{
	return this->pimpl->startingLifeTotal;
}

void Rules::setPoisonCounterLimit(std::size_t x)
{
	this->pimpl->poisonCounterLimit = x;
}

std::size_t Rules::getPoisonCounterLimit() const
{
	return this->pimpl->poisonCounterLimit;
}
