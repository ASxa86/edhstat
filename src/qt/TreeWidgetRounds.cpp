#include <qt/TreeWidgetRounds.h>

#include <core/Game.h>
#include <core/PimplImpl.h>
#include <core/Player.h>
#include <core/PlayerTurn.h>
#include <core/Round.h>
#include <core/TurnAction.h>

using namespace edh::core;
using namespace edh::qt;

Q_DECLARE_METATYPE(std::weak_ptr<edh::core::Round>)
Q_DECLARE_METATYPE(std::weak_ptr<edh::core::PlayerTurn>)
Q_DECLARE_METATYPE(std::weak_ptr<edh::core::TurnAction>)

struct TreeWidgetRounds::Impl
{
	enum Column : int
	{
		Name,
		ActionCount,
		ActionType,
		Target,
		Count
	};

	enum ItemType : int
	{
		Round = QTreeWidgetItem::UserType + 1,
		Turn,
		Action
	};

	std::weak_ptr<Game> game;
};

TreeWidgetRounds::TreeWidgetRounds(QWidget* parent) : QTreeWidget(parent)
{
	qRegisterMetaType<std::weak_ptr<edh::core::Round>>();
	qRegisterMetaType<std::weak_ptr<edh::core::PlayerTurn>>();
	qRegisterMetaType<std::weak_ptr<edh::core::TurnAction>>();

	this->setColumnCount(Impl::Column::Count);
	this->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectItems);
	this->setEditTriggers(QAbstractItemView::EditTrigger::AnyKeyPressed | QAbstractItemView::EditTrigger::DoubleClicked);

	QStringList header;
	header << "Round";
	header << "Count";
	header << "Action";
	header << "Target";
	this->setHeaderLabels(header);

	this->connect(this, &QTreeWidget::itemChanged, [this](QTreeWidgetItem* item, int column) {
		const auto itemType = static_cast<Impl::ItemType>(item->type());

		switch(itemType)
		{
			case Impl::ItemType::Round:
				break;
			case Impl::ItemType::Turn:
				break;
			case Impl::ItemType::Action:
			{
				auto action = item->data(0, Qt::UserRole).value<std::weak_ptr<TurnAction>>().lock();

				if(action != nullptr)
				{
					switch(static_cast<Impl::Column>(column))
					{
						case Impl::Column::Name:
							break;
						case Impl::Column::ActionCount:
							action->setCount(item->data(column, Qt::DisplayRole).toInt());
							break;
						case Impl::Column::ActionType:
							action->setType(static_cast<TurnAction::Type>(item->data(column, Qt::UserRole).toInt()));
							break;
						case Impl::Column::Target:
							break;
					}
				}
			}

			break;
		}
	});
}

TreeWidgetRounds::~TreeWidgetRounds()
{
}

void TreeWidgetRounds::setGame(const std::shared_ptr<Game>& x)
{
	this->pimpl->game = x;

	if(x != nullptr)
	{
		const auto rounds = x->getRounds();

		auto count = 0;

		for(const auto& round : rounds)
		{
			auto roundItem = new QTreeWidgetItem(Impl::ItemType::Round);
			roundItem->setText(Impl::Column::Name, "Round - " + QString::number(++count));
			std::weak_ptr<Round> weakRound = round;
			roundItem->setData(0, Qt::UserRole, QVariant::fromValue(weakRound));

			const auto turns = round->getPlayerTurns();

			for(const auto& turn : turns)
			{
				auto turnItem = new QTreeWidgetItem(Impl::ItemType::Turn);
				turnItem->setText(Impl::Column::Name, QString::fromStdString(turn->getPlayer()->getName()));
				std::weak_ptr<PlayerTurn> weakTurn = turn;
				turnItem->setData(0, Qt::UserRole, QVariant::fromValue(weakTurn));

				const auto actions = turn->getTurnActions();

				for(const auto& action : actions)
				{
					auto actionItem = new QTreeWidgetItem(Impl::ItemType::Action);
					actionItem->setData(Impl::Column::ActionCount, Qt::DisplayRole, action->getCount());
					actionItem->setData(Impl::Column::ActionType, Qt::UserRole, static_cast<int>(action->getType()));
					actionItem->setData(Impl::Column::ActionType, Qt::DisplayRole, QString::fromStdString(ToString(action->getType())));
					actionItem->setData(Impl::Column::Target, Qt::DisplayRole, QString::fromStdString(action->getTarget()->getName()));
					std::weak_ptr<TurnAction> weakAction = action;
					actionItem->setData(0, Qt::UserRole, QVariant::fromValue(weakAction));
					actionItem->setFlags(actionItem->flags() | Qt::ItemIsEditable);

					turnItem->addChild(actionItem);
				}

				roundItem->addChild(turnItem);
			}

			this->addTopLevelItem(roundItem);
		}
	}
}
