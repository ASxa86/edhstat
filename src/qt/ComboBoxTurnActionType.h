#pragma once

#include <qt/Export.h>
#include <core/TurnAction.h>
#include <QtWidgets/QComboBox>

namespace edh
{
	namespace qt
	{
		///
		///	\class ComboBoxTurnActionType
		///
		///	\brief This widget provides a combo box for editing the enumeration TurnAction::Type.
		///
		///	\date March 3, 2018
		///
		///	\author Aaron Shelley
		///
		class EDHQT_EXPORT ComboBoxTurnActionType : public QComboBox
		{
			Q_OBJECT

		public:
			ComboBoxTurnActionType(QWidget* parent = nullptr);
			~ComboBoxTurnActionType();

			void setCurrentType(edh::core::TurnAction::Type x);
			edh::core::TurnAction::Type getCurrentType() const;
		};
	}
}
