#include <qt/TableWidgetPlayer.h>

#include <core/Game.h>
#include <core/Player.h>
#include <qt/PlayerTableModel.h>
#include <QtWidgets/QHeaderView>

using namespace edh::core;
using namespace edh::qt;

Q_DECLARE_METATYPE(std::weak_ptr<edh::core::Player>)

TableWidgetPlayer::TableWidgetPlayer(QWidget* parent) : QTableView(parent)
{
	qRegisterMetaType<std::weak_ptr<edh::core::Player>>();

	this->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
	this->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
	this->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
	this->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
}

TableWidgetPlayer::~TableWidgetPlayer()
{
}

void TableWidgetPlayer::setGame(const std::shared_ptr<Game>& x)
{
	this->setModel(new PlayerTableModel(x));
}

std::shared_ptr<edh::core::Player> TableWidgetPlayer::getCurrentPlayer() const
{
	const auto indices = this->selectionModel()->selectedRows();

	if(indices.empty() == false)
	{
		return indices[0].data(Qt::UserRole).value<std::weak_ptr<Player>>().lock();
	}

	return nullptr;
}
