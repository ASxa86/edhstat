#pragma once

#include <core/Pimpl.h>
#include <qt/Export.h>
#include <QtWidgets/QTreeWidget>

namespace edh
{
	namespace core
	{
		class Game;
		class PlayerTurn;
		class Round;
		class TurnAction;
	}

	namespace qt
	{
		///
		///	\class TreeWidgetRounds
		///
		///	\brief This widget represents the rounds in a game of magic and provides an editing interface for the data contained within.
		///
		///	\date March 3, 2018
		///
		///	\author Aaron Shelley
		///
		class EDHQT_EXPORT TreeWidgetRounds : public QTreeWidget
		{
			Q_OBJECT

		public:
			TreeWidgetRounds(QWidget* parent = nullptr);
			~TreeWidgetRounds();

			void setGame(const std::shared_ptr<edh::core::Game>& x);

		protected:
			QTreeWidgetItem* createItem(const std::shared_ptr<edh::core::Round>& x);
			QTreeWidgetItem* createItem(const std::shared_ptr<edh::core::PlayerTurn>& x);
			QTreeWidgetItem* createItem(const std::shared_ptr<edh::core::TurnAction>& x);

		private:
			struct Impl;
			Pimpl<Impl> pimpl;
		};
	}
}
