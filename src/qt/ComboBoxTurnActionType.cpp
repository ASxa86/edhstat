#include <qt/ComboBoxTurnActionType.h>

using namespace edh::core;
using namespace edh::qt;

ComboBoxTurnActionType::ComboBoxTurnActionType(QWidget* parent) : QComboBox(parent)
{
	this->addItem(QString::fromStdString(ToString(TurnAction::Type::CardDraw)), static_cast<int>(TurnAction::Type::CardDraw));
	this->addItem(QString::fromStdString(ToString(TurnAction::Type::LandPlay)), static_cast<int>(TurnAction::Type::LandPlay));
	this->addItem(QString::fromStdString(ToString(TurnAction::Type::SpellPlay)), static_cast<int>(TurnAction::Type::SpellPlay));
	this->addItem(QString::fromStdString(ToString(TurnAction::Type::LifeGain)), static_cast<int>(TurnAction::Type::LifeGain));
	this->addItem(QString::fromStdString(ToString(TurnAction::Type::LifeLoss)), static_cast<int>(TurnAction::Type::LifeLoss));
}

ComboBoxTurnActionType::~ComboBoxTurnActionType()
{
}

void ComboBoxTurnActionType::setCurrentType(TurnAction::Type x)
{
	this->setCurrentIndex(this->findData(static_cast<int>(x)));
}

TurnAction::Type ComboBoxTurnActionType::getCurrentType() const
{
	return static_cast<TurnAction::Type>(this->currentData().toInt());
}
