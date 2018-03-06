#include <qt/GroupBoxGroup.h>

#include <core/PimplImpl.h>
#include <qt/GroupBoxPlayer.h>
#include <QtCore/QPointer>

using namespace edh::qt;

struct GroupBoxGroup::Impl
{
	std::vector<GroupBoxPlayer*> groups;
	QPointer<GroupBoxPlayer> checked;
};

GroupBoxGroup::GroupBoxGroup(QObject* parent) : QObject(parent)
{
}

GroupBoxGroup::~GroupBoxGroup()
{
}

void GroupBoxGroup::addGroupBox(GroupBoxPlayer* x)
{
	this->pimpl->groups.push_back(x);

	x->setGroupBoxGroup(this);
}

void GroupBoxGroup::removeGroupBox(GroupBoxPlayer* x)
{
	this->pimpl->groups.erase(std::remove(std::begin(this->pimpl->groups), std::end(this->pimpl->groups), x), std::end(this->pimpl->groups));
}

void GroupBoxGroup::setCheckedGroupBox(GroupBoxPlayer* x)
{
	this->pimpl->checked = x;
}

GroupBoxPlayer* GroupBoxGroup::getCheckedGroupBox() const
{
	return this->pimpl->checked;
}
