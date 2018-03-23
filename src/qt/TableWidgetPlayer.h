#pragma once

#include <qt/Export.h>
#include <QtWidgets/QTableView>

namespace edh
{
	namespace core
	{
		class Game;
		class Player;
	}

	namespace qt
	{
		///
		///	\class TableWidgetPlayer
		///
		///	\brief A table widget to manage the players in a game.
		///
		///	\date March 22, 2018
		///
		///	\author Aaron Shelley
		///
		class EDHQT_EXPORT TableWidgetPlayer : public QTableView
		{
			Q_OBJECT

		public:
			TableWidgetPlayer(QWidget* parent = nullptr);
			virtual ~TableWidgetPlayer() override;

			void setGame(const std::shared_ptr<edh::core::Game>& x);

			std::shared_ptr<edh::core::Player> getCurrentPlayer() const;
		};
	}
}