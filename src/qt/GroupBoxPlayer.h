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
		class GroupBoxGroup;

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
			virtual ~GroupBoxPlayer();

			void setPlayer(const std::shared_ptr<edh::core::Player>&  x);
			std::shared_ptr<edh::core::Player> getPlayer() const;

			void setChecked(bool x);

		protected:
			void mouseReleaseEvent(QMouseEvent* event) override;

		private:
			friend class GroupBoxGroup;
			void setGroupBoxGroup(GroupBoxGroup* x);

			struct Impl;
			Pimpl<Impl> pimpl;
		};
	}
}
