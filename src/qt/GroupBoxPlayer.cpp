#include <qt/GroupBoxPlayer.h>

#include <core/PimplImpl.h>
#include <core/Player.h>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

using namespace edh::core;
using namespace edh::qt;

struct GroupBoxPlayer::Impl
{
	QLabel* lblLifeTotal{nullptr};
	Player* player{nullptr};
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

		if(this->pimpl->player != nullptr)
		{
			const auto lifeTotal = this->pimpl->player->getLifeTotal();
			this->pimpl->player->setLifeTotal(lifeTotal + x);

			this->pimpl->lblLifeTotal->setText(QString::number(this->pimpl->player->getLifeTotal()));
		}
	};

	this->connect(btnPlusOne, &QPushButton::clicked, [adjustLifeTotal] {
		adjustLifeTotal(1);
	});

	this->connect(btnPlusFive, &QPushButton::clicked, [adjustLifeTotal] {
		adjustLifeTotal(5);
	});

	this->connect(btnMinusOne, &QPushButton::clicked, [adjustLifeTotal] {
		adjustLifeTotal(-1);
	});

	this->connect(btnMinusFive, &QPushButton::clicked, [adjustLifeTotal] {
		adjustLifeTotal(-5);
	});
}

GroupBoxPlayer::~GroupBoxPlayer()
{
}

void GroupBoxPlayer::setPlayer(edh::core::Player* x)
{
	this->pimpl->player = x;

	if(this->pimpl->player != nullptr)
	{
		this->setTitle(QString::fromStdString(this->pimpl->player->getName()));
		this->pimpl->lblLifeTotal->setText(QString::number(this->pimpl->player->getLifeTotal()));
	}
}
