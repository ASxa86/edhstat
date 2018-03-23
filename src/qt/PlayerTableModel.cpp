#include <qt/PlayerTableModel.h>

#include <core/Game.h>
#include <core/PimplImpl.h>
#include <core/Player.h>
#include <boost/signals2/connection.hpp>

using namespace edh::core;
using namespace edh::qt;

Q_DECLARE_METATYPE(std::weak_ptr<edh::core::Player>)

struct PlayerTableModel::Impl
{
	Impl(const std::shared_ptr<Game>& x) : game{x}
	{
	}

	std::vector<boost::signals2::scoped_connection> connections;
	std::weak_ptr<Game> game;
};

PlayerTableModel::PlayerTableModel(const std::shared_ptr<edh::core::Game>& game, QObject* parent) : QAbstractTableModel{parent}, pimpl{game}
{
	qRegisterMetaType<std::weak_ptr<edh::core::Player>>();

	const auto dataChanged = [this](std::shared_ptr<Player> x) {
		const auto game = this->pimpl->game.lock();

		if(game != nullptr)
		{
			const auto row = game->indexOfPlayer(x);
			this->dataChanged(this->index(row, Column::Name), this->index(row, Column::Count - 1));
		}
	};

	this->pimpl->connections.push_back(game->addAddPlayerObserver([this, dataChanged](std::shared_ptr<Player> x) {
		const auto game = this->pimpl->game.lock();

		if(game != nullptr)
		{
			const auto row = game->indexOfPlayer(x);
			this->beginInsertRows(QModelIndex(), row, row);

			this->pimpl->connections.push_back(x->addDirtyObserver(dataChanged));

			this->endInsertRows();
		}
	}));

	this->pimpl->connections.push_back(game->addRemovePlayerObserver([this](std::shared_ptr<Player> x) {
		const auto game = this->pimpl->game.lock();

		if(game != nullptr)
		{
			const auto row = game->indexOfPlayer(x);
			this->beginRemoveRows(QModelIndex(), row, row);
			this->endRemoveRows();
		}
	}));

	const auto players = game->getPlayers();

	for(const auto& player : players)
	{
		this->pimpl->connections.push_back(player->addDirtyObserver(dataChanged));
	}
}

PlayerTableModel::~PlayerTableModel()
{
}

int PlayerTableModel::columnCount(const QModelIndex&) const
{
	return Column::Count;
}

int PlayerTableModel::rowCount(const QModelIndex&) const
{
	const auto game = this->pimpl->game.lock();

	if(game != nullptr)
	{
		return static_cast<int>(game->getPlayers().size());
	}

	return 0;
}

QVariant PlayerTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	QVariant data;

	if(role == Qt::DisplayRole)
	{
		switch(orientation)
		{
			case Qt::Orientation::Horizontal:
			{
				switch(static_cast<Column>(section))
				{
					case Column::Name:
						data = "Name";
						break;

					case Column::LifeTotal:
						data = "Life";
						break;

					case Column::PoisonCounters:
						data = "Poison";
						break;

					case Column::ExperienceCounters:
						data = "Experience";
						break;
				}
			}
			break;

			case Qt::Orientation::Vertical:
				data = section + 1;
				break;
		}
	}

	return data;
}

bool PlayerTableModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	const auto game = this->pimpl->game.lock();

	if(index.isValid() == true && game != nullptr)
	{
		const auto players = game->getPlayers();
		const auto player = players[index.row()];

		if(role == Qt::EditRole)
		{
			switch(static_cast<Column>(index.column()))
			{
				case Column::Name:
					player->setName(value.toString().toStdString());
					break;
				case Column::LifeTotal:
					player->setLifeTotal(value.toInt());
					break;

				case Column::PoisonCounters:
					player->setPoisonCounters(value.toInt());
					break;

				case Column::ExperienceCounters:
					player->setExperienceCounters(value.toInt());
					break;
			}
		}

		player->makeDirty();
		return true;
	}

	return false;
}

QVariant PlayerTableModel::data(const QModelIndex& index, int role) const
{
	QVariant data;

	const auto game = this->pimpl->game.lock();
	if(index.isValid() == true && game != nullptr)
	{
		const auto players = game->getPlayers();
		const auto& player = players[index.row()];

		if(role == Qt::DisplayRole || role == Qt::EditRole)
		{
			switch(static_cast<Column>(index.column()))
			{
				case Column::Name:
					data = QString::fromStdString(player->getName());
					break;

				case Column::LifeTotal:
					data = player->getLifeTotal();
					break;

				case Column::PoisonCounters:
					data = player->getPoisonCounters();
					break;

				case Column::ExperienceCounters:
					data = player->getExperienceCounters();
					break;
			}
		}
		else if(role == Qt::UserRole)
		{
			std::weak_ptr<Player> weakPlayer = player;
			data = QVariant::fromValue(weakPlayer);
		}
	}

	return data;
}

Qt::ItemFlags PlayerTableModel::flags(const QModelIndex& index) const
{
	Qt::ItemFlags flags;

	if(index.isValid() == true)
	{
		switch(static_cast<Column>(index.column()))
		{
		case Column::Name:
			flags |= Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
			break;
		default:
			flags = this->QAbstractTableModel::flags(index);
		}
	}

	return flags;
}
