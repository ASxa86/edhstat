#include <core/Object.h>
#include <core/PimplImpl.h>
#include <core/signals.hpp>

#include <algorithm>

using namespace edh::core;

class Object::Impl
{
	public:
		Impl(const std::string& x) :
			parent(nullptr),
			id(x)
		{
		}

		std::vector<std::unique_ptr<Object>> children;
		Object* parent;
		std::string id;

		signals::signal<void(Object*)> addChildSignal;
		signals::signal<void(Object*)> removeChildSignal;
		signals::signal<void()> startupSignal;
		signals::connections connections;
};

Object::Object(const std::string& x) :
	pimpl(x)
{
}

Object::~Object()
{
}

void Object::setID(const std::string& x)
{
	this->pimpl->id = x;
}

std::string Object::getID() const
{
	return this->pimpl->id;
}

bool Object::addChild(std::unique_ptr<Object> x)
{
	auto it = std::find(std::begin(this->pimpl->children), std::end(this->pimpl->children), x);
	
	if(it == std::end(this->pimpl->children))
	{
		x->setParent(this);
		auto child = x.get();
		this->pimpl->children.push_back(std::move(x));
		this->pimpl->addChildSignal.fire(child);
		return true;
	}

	return false;
}

bool Object::removeChild(Object* x)
{
	auto it = std::remove_if(std::begin(this->pimpl->children), std::end(this->pimpl->children),
		[x](std::unique_ptr<Object>& child)
		{
			return x == child.get();
		});
	
	if(it != std::end(this->pimpl->children))
	{
		this->pimpl->removeChildSignal.fire((*it).get());
		this->pimpl->children.erase(it, std::end(this->pimpl->children));
		return true;
	}

	return false;
}

Object* Object::getChild(size_t x) const
{
	if(x < this->pimpl->children.size())
	{
		return this->pimpl->children[x].get();
	}

	return nullptr;
}

Object* Object::getChild(const std::string& x) const
{
	for(const auto& child : this->pimpl->children)
	{
		if(child->getID() == x)
		{
			return child.get();
		}
	}

	return nullptr;
}

const std::vector<std::unique_ptr<Object>>& Object::getChildren() const
{
	return this->pimpl->children;
}

void Object::setParent(Object* x)
{
	this->pimpl->parent = x;
}

Object* Object::getParent() const
{
	return this->pimpl->parent;
}

void Object::addAddChildObserver(const std::function<void(Object*)>& x)
{
	this->pimpl->connections.connect(this->pimpl->addChildSignal, x);
}

void Object::addRemoveChildObserver(const std::function<void(Object*)>& x)
{
	this->pimpl->connections.connect(this->pimpl->removeChildSignal, x);
}
