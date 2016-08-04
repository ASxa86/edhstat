#pragma once

#include <QtWidgets/QGroupBox>

#include <qt/Export.h>
#include <core/Pimpl.h>


namespace edh
{
	namespace core
	{
		class Player;
	}

	namespace qt
	{
		///
		///	\class PlayerWidget
		///
		///	\brief This widget renders a single player's current state and allows for modify said state.
		///
		///	\date August 3, 2016
		///
		///	\author Aaron Shelley
		///
		class EDHQT_EXPORT PlayerWidget : public QGroupBox
		{
			Q_OBJECT

			public:
				PlayerWidget(edh::core::Player* player, QWidget* parent = nullptr);
				~PlayerWidget() override;

			protected:
				void btnMinusOneClicked();
				void btnPlusOneClicked();
				void btnMinusFiveClicked();
				void btnPlusFiveClicked();

			private:
				class Impl;
				Pimpl<Impl> pimpl;
		};
	}
}
