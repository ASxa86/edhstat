#include <core/Object.h>

#include <core/PimplImpl.h>
#include <boost/signals2/signal.hpp>

using namespace edh::core;

struct Object::Impl
{
	boost::signals2::signal<void(std::shared_ptr<Object>)> dirtyObservers;
};

Object::Object()
{
}

Object::~Object()
{
}

boost::signals2::connection Object::addDirtyObserver(const std::function<void(std::shared_ptr<Object>)>& x)
{
	return this->pimpl->dirtyObservers.connect(x);
}

void Object::makeDirty()
{
	this->pimpl->dirtyObservers(this->shared_from_this());
}
