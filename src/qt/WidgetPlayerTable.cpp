#include <qt/WidgetPlayerTable.h>

#include <core/Game.h>
#include <core/PimplImpl.h>
#include <core/Player.h>

using namespace edh::core;
using namespace edh::qt;

Q_DECLARE_METATYPE(std::weak_ptr<edh::core::Player>)

struct WidgetPlayerTable::Impl
{
	enum Column : int
	{
		Player,
		Life,
		Poison,
		Experience,
		Count
	};

	std::weak_ptr<Game> game;
};

WidgetPlayerTable::WidgetPlayerTable(QWidget* parent) : QTableWidget(parent), pimpl()
{
	qRegisterMetaType<std::weak_ptr<edh::core::Player>>();

	this->setColumnCount(Impl::Column::Count);

	QStringList header;
	header << "Player";
	header << " Life";
	header << "Poison";
	header << "Experience";
	this->setHorizontalHeaderLabels(header);

	this->connect(this->model(), &QAbstractItemModel::dataChanged, [this](const QModelIndex& index) {
		const auto variant = this->model()->data(this->model()->index(index.row(), Impl::Column::Player), Qt::UserRole);

		const auto player = variant.value<std::weak_ptr<Player>>().lock();

		if(player != nullptr)
		{
			switch(static_cast<Impl::Column>(index.column()))
			{
				case Impl::Column::Player:
					player->setName(index.data().toString().toStdString());
					break;

				case Impl::Column::Life:
					player->setLifeTotal(index.data().toInt());
					break;

				case Impl::Column::Poison:
					player->setPoisonCounters(index.data().toInt());
					break;

				case Impl::Column::Experience:
					player->setExperienceCounters(index.data().toInt());
					break;
			}
		}
	});
}

WidgetPlayerTable::~WidgetPlayerTable()
{
}

void WidgetPlayerTable::setGame(const std::shared_ptr<edh::core::Game>& x)
{
	this->setRowCount(0);

	this->pimpl->game = x;

	if(x != nullptr)
	{
		const auto players = x->getPlayers();
		const auto playerCount = static_cast<int>(players.size());
		this->setRowCount(playerCount);

		for(auto i = 0; i < playerCount; i++)
		{
			const auto& player = players[i];

			const auto index = [this](int r, int c) { return this->model()->index(r, c); };
			std::weak_ptr<Player> weakPlayer;
			this->model()->setData(index(i, Impl::Column::Player), QVariant::fromValue(weakPlayer), Qt::UserRole);
			this->model()->setData(index(i, Impl::Column::Player), QString::fromStdString(player->getName()));
			this->model()->setData(index(i, Impl::Column::Life), player->getLifeTotal());
			this->model()->setData(index(i, Impl::Column::Poison), player->getPoisonCounters());
			this->model()->setData(index(i, Impl::Column::Experience), player->getExperienceCounters());
		}
	}
}
