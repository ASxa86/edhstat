#include <qt/TreeWidgetRounds.h>

#include <core/Game.h>
#include <core/PimplImpl.h>
#include <core/Player.h>
#include <core/PlayerTurn.h>
#include <core/Round.h>
#include <core/TurnAction.h>
#include <qt/DelegatePlayer.h>
#include <qt/DelegateTurnActionType.h>
#include <QtWidgets/QHeaderView>
#include <QtCore/QDateTime>

using namespace edh::core;
using namespace edh::qt;

Q_DECLARE_METATYPE(std::weak_ptr<edh::core::Round>)
Q_DECLARE_METATYPE(std::weak_ptr<edh::core::Player>)
Q_DECLARE_METATYPE(std::weak_ptr<edh::core::PlayerTurn>)
Q_DECLARE_METATYPE(std::weak_ptr<edh::core::TurnAction>)

struct TreeWidgetRounds::Impl
{
	enum Column : int
	{
		Name,
		Time,
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

	std::vector<boost::signals2::scoped_connection> connections;
	std::weak_ptr<Game> game;
	DelegatePlayer* dlgPlayer{new DelegatePlayer()};
};

TreeWidgetRounds::TreeWidgetRounds(QWidget* parent) : QTreeWidget(parent)
{
	qRegisterMetaType<std::weak_ptr<edh::core::Round>>();
	qRegisterMetaType<std::weak_ptr<edh::core::Player>>();
	qRegisterMetaType<std::weak_ptr<edh::core::PlayerTurn>>();
	qRegisterMetaType<std::weak_ptr<edh::core::TurnAction>>();

	this->setColumnCount(Impl::Column::Count);
	this->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectItems);
	this->setEditTriggers(QAbstractItemView::EditTrigger::AnyKeyPressed | QAbstractItemView::EditTrigger::DoubleClicked);
	this->header()->setStretchLastSection(false);
	this->header()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);

	this->setItemDelegateForColumn(Impl::Column::ActionType, new DelegateTurnActionType());
	this->setItemDelegateForColumn(Impl::Column::Target, this->pimpl->dlgPlayer);

	QStringList header;
	header << "Round";
	header << "Time";
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
		this->pimpl->dlgPlayer->setGame(x);

		x->addAddRoundObserver([this](auto round) {
			auto roundItem = this->createItem(round);
			this->addTopLevelItem(roundItem);

			round->addAddTurnObserver([this, roundItem](auto turn) {
				roundItem->addChild(this->createItem(turn));
			});
		});

		const auto rounds = x->getRounds();

		for(const auto& round : rounds)
		{
			this->addTopLevelItem(this->createItem(round));
		}
	}
}

QTreeWidgetItem* TreeWidgetRounds::createItem(const std::shared_ptr<edh::core::Round>& x)
{
	auto roundItem = new QTreeWidgetItem(Impl::ItemType::Round);
	roundItem->setText(Impl::Column::Name, "Round - " + QString::number(this->pimpl->game.lock()->getRounds().size()));
	std::weak_ptr<Round> weakRound = x;
	roundItem->setData(0, Qt::UserRole, QVariant::fromValue(weakRound));

	const auto turns = x->getPlayerTurns();

	for(const auto& turn : turns)
	{
		roundItem->addChild(this->createItem(turn));
	}

	return roundItem;
}

QTreeWidgetItem* TreeWidgetRounds::createItem(const std::shared_ptr<edh::core::PlayerTurn>& x)
{
	auto turnItem = new QTreeWidgetItem(Impl::ItemType::Turn);
	turnItem->setText(Impl::Column::Name, QString::fromStdString("Turn - " + x->getPlayer()->getName()));
	turnItem->setText(Impl::Column::Time, QDateTime::fromTime_t(x->getTime().count()).toUTC().toString("mm:ss"));
	this->pimpl->connections.push_back(x->addDirtyObserver([turnItem](auto turn) {
		turnItem->setText(Impl::Column::Time, QDateTime::fromTime_t(turn->getTime().count()).toUTC().toString("mm:ss"));
	}));


	std::weak_ptr<PlayerTurn> weakTurn = x;
	turnItem->setData(0, Qt::UserRole, QVariant::fromValue(weakTurn));

	const auto actions = x->getTurnActions();

	for(const auto& action : actions)
	{
		turnItem->addChild(this->createItem(action));
	}

	return turnItem;
}

QTreeWidgetItem* TreeWidgetRounds::createItem(const std::shared_ptr<edh::core::TurnAction>& x)
{
	auto actionItem = new QTreeWidgetItem(Impl::ItemType::Action);
	actionItem->setData(Impl::Column::ActionCount, Qt::DisplayRole, x->getCount());
	actionItem->setData(Impl::Column::ActionType, Qt::UserRole, static_cast<int>(x->getType()));
	actionItem->setData(Impl::Column::ActionType, Qt::DisplayRole, QString::fromStdString(ToString(x->getType())));

	std::weak_ptr<Player> weakPlayer = x->getTarget();
	actionItem->setData(Impl::Column::Target, Qt::UserRole, QVariant::fromValue(weakPlayer));
	actionItem->setData(Impl::Column::Target, Qt::DisplayRole, QString::fromStdString(x->getTarget()->getName()));
	std::weak_ptr<TurnAction> weakAction = x;
	actionItem->setData(0, Qt::UserRole, QVariant::fromValue(weakAction));
	actionItem->setFlags(actionItem->flags() | Qt::ItemIsEditable);

	return actionItem;
}
