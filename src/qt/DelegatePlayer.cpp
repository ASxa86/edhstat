#include <qt/DelegatePlayer.h>

#include <core/PimplImpl.h>
#include <core/Player.h>
#include <qt/ComboBoxPlayer.h>

using namespace edh::core;
using namespace edh::qt;

Q_DECLARE_METATYPE(std::weak_ptr<edh::core::Player>)

struct DelegatePlayer::Impl
{
	std::weak_ptr<Game> game;
};

DelegatePlayer::DelegatePlayer(QObject* parent) : QStyledItemDelegate(parent)
{
	qRegisterMetaType<std::weak_ptr<edh::core::Player>>();
}

DelegatePlayer::~DelegatePlayer()
{
}

QString DelegatePlayer::displayText(const QVariant& value, const QLocale&) const
{
	QString s;

	const auto player = value.value<std::weak_ptr<edh::core::Player>>().lock();

	if(player != nullptr)
	{
		s = QString::fromStdString(player->getName());
	}

	return s;
}

QWidget* DelegatePlayer::createEditor(QWidget* parent, const QStyleOptionViewItem&, const QModelIndex&) const
{
	auto editor = new ComboBoxPlayer(parent);
	editor->setGame(this->pimpl->game.lock());
	this->connect(editor, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &DelegatePlayer::commitAndCloseEditor);

	return editor;
}

void DelegatePlayer::setEditorData(QWidget* editor, const QModelIndex& index) const
{
	static_cast<ComboBoxPlayer*>(editor)->setCurrentPlayer(index.data().value<std::weak_ptr<Player>>().lock());
}

void DelegatePlayer::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
	std::weak_ptr<Player> weakPlayer = static_cast<ComboBoxPlayer*>(editor)->getCurrentPlayer();
	model->setData(index, QVariant::fromValue(weakPlayer));
}

void DelegatePlayer::setGame(const std::shared_ptr<Game>& x)
{
	this->pimpl->game = x;
}

void DelegatePlayer::commitAndCloseEditor()
{
	auto editor = static_cast<ComboBoxPlayer*>(this->sender());
	this->commitData(editor);
	this->closeEditor(editor);
}
