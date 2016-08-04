#include <qt/PlayerWidget.h>
#include <core/PimplImpl.h>

#include <core/Player.h>
#include <logger/Logger.h>

#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>

using namespace edh::core;
using namespace edh::qt;

class PlayerWidget::Impl
{
	public:
		Impl(Player* p) :
			player(p),
			lblCurrent(new QLabel(QString::number(p->getLifeTotal()))),
			btnPlusOne(new QPushButton("+1")),
			btnMinusOne(new QPushButton("-1")),
			btnPlusFive(new QPushButton("+5")),
			btnMinusFive(new QPushButton("-5")),
			rdLife(new QRadioButton("Life")),
			rdPsn(new QRadioButton("Psn")),
			rdExp(new QRadioButton("Exp")),
			fineIncrement(1),
			coarseIncrement(5)
		{
			this->rdLife->setChecked(true);
		}

		~Impl()
		{
			this->player = nullptr;
		}

		void incrementPlayer(int x)
		{
			if(this->rdLife->isChecked() == true)
			{
				this->player->setLifeTotal(this->player->getLifeTotal() + x);
			}
			else if(this->rdPsn->isChecked() == true)
			{
				this->player->setPoisonCounters(this->player->getPoisonCounters() + x);
			}
			else if(this->rdExp->isChecked() == true)
			{
				this->player->setExperienceCounters(this->player->getExperienceCounters() + x);
			}
		}

		void updateWidget()
		{
			this->btnMinusOne->setEnabled(true);
			this->btnMinusFive->setEnabled(true);

			if(this->rdLife->isChecked() == true)
			{
				this->lblCurrent->setText(QString::number(this->player->getLifeTotal()));
			}
			else if(this->rdPsn->isChecked() == true)
			{
				this->lblCurrent->setText(QString::number(this->player->getPoisonCounters()));

				if(this->player->getPoisonCounters() < this->coarseIncrement)
				{
					this->btnMinusFive->setEnabled(false);
				}
				
				if(this->player->getPoisonCounters() < this->fineIncrement)
				{
					this->btnMinusOne->setEnabled(false);
				}
			}
			else if(this->rdExp->isChecked() == true)
			{
				this->lblCurrent->setText(QString::number(this->player->getExperienceCounters()));

				if(this->player->getExperienceCounters() < this->coarseIncrement)
				{
					this->btnMinusFive->setEnabled(false);
				}
				
				if(this->player->getExperienceCounters() < this->fineIncrement)
				{
					this->btnMinusOne->setEnabled(false);
				}
			}
		}

		Player* player;

		QLabel* lblCurrent;

		QPushButton* btnPlusOne;
		QPushButton* btnMinusOne;
		QPushButton* btnPlusFive;
		QPushButton* btnMinusFive;

		QRadioButton* rdLife;
		QRadioButton* rdPsn;
		QRadioButton* rdExp;

		int fineIncrement;
		int coarseIncrement;
};

PlayerWidget::PlayerWidget(Player* player, QWidget* parent) : QGroupBox(parent),
	pimpl(player)
{
	this->setTitle(QString::fromStdString(player->getID()));

	auto vLayout = new QVBoxLayout(this);

	auto hLayout = new QHBoxLayout();

	auto radioButtonLayout = new QVBoxLayout();
	auto radioGroup = new QButtonGroup(this);

	radioGroup->addButton(this->pimpl->rdLife);
	radioGroup->addButton(this->pimpl->rdPsn);
	radioGroup->addButton(this->pimpl->rdExp);

	radioButtonLayout->addWidget(this->pimpl->rdLife);
	radioButtonLayout->addWidget(this->pimpl->rdPsn);
	radioButtonLayout->addWidget(this->pimpl->rdExp);

	this->pimpl->lblCurrent = new QLabel(QString::number(player->getLifeTotal()));
	this->pimpl->lblCurrent->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

	auto font = this->pimpl->lblCurrent->font();
	font.setPointSize(40);
	this->pimpl->lblCurrent->setFont(font);

	hLayout->addLayout(radioButtonLayout);
	hLayout->addWidget(this->pimpl->lblCurrent);
	
	auto gLayout = new QGridLayout();

	auto sizePolicy = QSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
	this->pimpl->btnMinusOne->setSizePolicy(sizePolicy);
	this->pimpl->btnPlusOne->setSizePolicy(sizePolicy);
	this->pimpl->btnMinusFive->setSizePolicy(sizePolicy);
	this->pimpl->btnPlusFive->setSizePolicy(sizePolicy);

	auto row = 0;
	auto col = 0;
	gLayout->addWidget(this->pimpl->btnMinusOne, row, col);
	gLayout->addWidget(this->pimpl->btnPlusOne, row, ++col);
	gLayout->addWidget(this->pimpl->btnMinusFive, ++row, --col);
	gLayout->addWidget(this->pimpl->btnPlusFive, row, ++col);

	vLayout->addLayout(hLayout);
	vLayout->addLayout(gLayout);
	vLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding));

	this->connect(this->pimpl->rdLife, &QRadioButton::toggled, [this] { this->pimpl->updateWidget(); });
	this->connect(this->pimpl->rdPsn, &QRadioButton::toggled, [this] { this->pimpl->updateWidget(); });
	this->connect(this->pimpl->rdExp, &QRadioButton::toggled, [this] { this->pimpl->updateWidget(); });

	this->connect(this->pimpl->btnMinusOne, &QPushButton::clicked, this, &PlayerWidget::btnMinusOneClicked);
	this->connect(this->pimpl->btnPlusOne, &QPushButton::clicked, this, &PlayerWidget::btnPlusOneClicked);
	this->connect(this->pimpl->btnMinusFive, &QPushButton::clicked, this, &PlayerWidget::btnMinusFiveClicked);
	this->connect(this->pimpl->btnPlusFive, &QPushButton::clicked, this, &PlayerWidget::btnPlusFiveClicked);
}

PlayerWidget::~PlayerWidget()
{
}

void PlayerWidget::btnMinusOneClicked()
{
	this->pimpl->incrementPlayer(-this->pimpl->fineIncrement);
	this->pimpl->updateWidget();
}

void PlayerWidget::btnPlusOneClicked()
{
	this->pimpl->incrementPlayer(+this->pimpl->fineIncrement);
	this->pimpl->updateWidget();
}

void PlayerWidget::btnMinusFiveClicked()
{
	this->pimpl->incrementPlayer(-this->pimpl->coarseIncrement);
	this->pimpl->updateWidget();
}

void PlayerWidget::btnPlusFiveClicked()
{
	this->pimpl->incrementPlayer(+this->pimpl->coarseIncrement);
	this->pimpl->updateWidget();
}
