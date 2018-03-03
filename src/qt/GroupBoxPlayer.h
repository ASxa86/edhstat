#pragma once

#include <core/Pimpl.h>
#include <qt/Export.h>
#include <QtWidgets/QGroupBox>

namespace edh
{
	namespace core
	{
		class Player;
	}

	namespace qt
	{
		///
		///	\class WidgetPlayer
		///
		///	\brief This widget renders the state for a given Player.
		///
		///	\date March 3, 2018
		///
		///	\author Aaron Shelley
		///
		class EDHQT_EXPORT GroupBoxPlayer : public QGroupBox
		{
			Q_OBJECT

		public:
			GroupBoxPlayer(QWidget* parent = nullptr);
			~GroupBoxPlayer();

			void setPlayer(edh::core::Player*  x);

		protected:
		private:
			struct Impl;
			Pimpl<Impl> pimpl;
		};
	}
}
