#include <qt/GroupBoxPlayer.h>

#include <core/PimplImpl.h>
#include <core/Player.h>
#include <qt/GroupBoxGroup.h>
#include <QtCore/QPointer>
#include <QtGui/QMouseEvent>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

using namespace edh::core;
using namespace edh::qt;

struct GroupBoxPlayer::Impl
{
	QLabel* lblLifeTotal{nullptr};
	QPointer<GroupBoxGroup> group{nullptr};
	std::weak_ptr<Player> player{};

	const QString toggledSheet{
		"QGroupBox{border: 2px solid blue; margin-top: 0.5em;} QGroupBox::title{subcontrol-origin: margin; left: 10px; padding: 0 3px 0 3px;}"};
	bool toggled{false};
};

GroupBoxPlayer::GroupBoxPlayer(QWidget* parent) : QGroupBox(parent)
{
	const auto layout = new QGridLayout(this);
	layout->setMargin(0);
	layout->setSpacing(0);

	this->pimpl->lblLifeTotal = new QLabel("40");
	auto f = this->pimpl->lblLifeTotal->font();
	f.setPointSize(40);
	this->pimpl->lblLifeTotal->setFont(f);

	const auto btnPlusOne = new QPushButton("+1");
	const auto btnPlusFive = new QPushButton("+5");
	const auto btnMinusOne = new QPushButton("-1");
	const auto btnMinusFive = new QPushButton("-5");

	layout->addWidget(this->pimpl->lblLifeTotal, 0, 0, 2, 2, Qt::AlignHCenter | Qt::AlignVCenter);
	layout->addWidget(btnMinusOne, 2, 0);
	layout->addWidget(btnPlusOne, 2, 1);
	layout->addWidget(btnMinusFive, 3, 0);
	layout->addWidget(btnPlusFive, 3, 1);

	const auto adjustLifeTotal = [this](int x) {
		const auto player = this->pimpl->player.lock();

		if(player != nullptr)
		{
			const auto lifeTotal = player->getLifeTotal();
			player->setLifeTotal(lifeTotal + x);

			this->pimpl->lblLifeTotal->setText(QString::number(player->getLifeTotal()));
		}
	};

	this->connect(btnPlusOne, &QPushButton::clicked, [adjustLifeTotal] { adjustLifeTotal(1); });
	this->connect(btnPlusFive, &QPushButton::clicked, [adjustLifeTotal] { adjustLifeTotal(5); });
	this->connect(btnMinusOne, &QPushButton::clicked, [adjustLifeTotal] { adjustLifeTotal(-1); });
	this->connect(btnMinusFive, &QPushButton::clicked, [adjustLifeTotal] { adjustLifeTotal(-5); });
}

GroupBoxPlayer::~GroupBoxPlayer()
{
	if(this->pimpl->group != nullptr)
	{
		this->pimpl->group->removeGroupBox(this);
	}
}

void GroupBoxPlayer::setPlayer(const std::shared_ptr<edh::core::Player>& x)
{
	this->pimpl->player = x;

	if(x != nullptr)
	{
		this->setTitle(QString::fromStdString(x->getName()));
		this->pimpl->lblLifeTotal->setText(QString::number(x->getLifeTotal()));
	}
}

void GroupBoxPlayer::setChecked(bool x)
{
	if(this->pimpl->toggled != x)
	{
		this->pimpl->toggled = x;

		if(this->pimpl->toggled == true)
		{
			this->setStyleSheet(this->pimpl->toggledSheet);
		}
		else
		{
			this->setStyleSheet("");
		}

		if(this->pimpl->group != nullptr)
		{
			if(this->pimpl->toggled == true)
			{
				auto previous = this->pimpl->group->getCheckedGroupBox();

				if(previous != nullptr)
				{
					previous->setChecked(false);
				}

				this->setChecked(true);
				this->pimpl->group->setCheckedGroupBox(this);
			}
		}

		this->toggled(this->pimpl->toggled);

		if(this->pimpl->group != nullptr)
		{
			this->pimpl->group->groupBoxToggled(this, this->pimpl->toggled);
		}
	}
}

void GroupBoxPlayer::mouseReleaseEvent(QMouseEvent* event)
{
	if(event->button() == Qt::MouseButton::LeftButton)
	{
		 this->setChecked(!this->pimpl->toggled);
	}
}

void GroupBoxPlayer::setGroupBoxGroup(GroupBoxGroup* x)
{
	this->pimpl->group = x;
}
