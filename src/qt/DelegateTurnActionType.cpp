#include <qt/DelegateTurnActionType.h>

#include <qt/ComboBoxTurnActionType.h>

using namespace edh::core;
using namespace edh::qt;

DelegateTurnActionType::DelegateTurnActionType(QObject* parent) : QStyledItemDelegate(parent)
{
}

DelegateTurnActionType::~DelegateTurnActionType()
{
}

QString DelegateTurnActionType::displayText(const QVariant& value, const QLocale&) const
{
	return QString::fromStdString(ToString(static_cast<TurnAction::Type>(value.toInt())));
}

QWidget* DelegateTurnActionType::createEditor(QWidget* parent, const QStyleOptionViewItem&, const QModelIndex&) const
{
	auto editor = new ComboBoxTurnActionType(parent);
	this->connect(editor, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &DelegateTurnActionType::commitAndCloseEditor);

	return editor;
}

void DelegateTurnActionType::setEditorData(QWidget* editor, const QModelIndex& index) const
{
	static_cast<ComboBoxTurnActionType*>(editor)->setCurrentType(static_cast<TurnAction::Type>(index.data(Qt::UserRole).toInt()));
}

void DelegateTurnActionType::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
	model->setData(index, static_cast<int>(static_cast<ComboBoxTurnActionType*>(editor)->getCurrentType()));
}

void DelegateTurnActionType::commitAndCloseEditor()
{
	auto editor = static_cast<ComboBoxTurnActionType*>(this->sender());
	this->commitData(editor);
	this->closeEditor(editor);
}
