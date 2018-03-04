#pragma once

#include <core/Pimpl.h>
#include <qt/Export.h>
#include <QComboBox>

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
		///	\class ComboBoxPlayer
		///
		///	\brief This widget allows for editing and selection of current players within the game.
		///
		///	\date March 4, 2018
		///
		///	\author Aaron Shelley
		///
		class EDHQT_EXPORT ComboBoxPlayer : public QComboBox
		{
			Q_OBJECT

		public:
			ComboBoxPlayer(QWidget* parent = nullptr);
			~ComboBoxPlayer();

			void setGame(const std::shared_ptr<edh::core::Game>& x);

			void setCurrentPlayer(const std::shared_ptr<edh::core::Player>& x);
			std::shared_ptr<edh::core::Player> getCurrentPlayer() const;

		private:
			struct Impl;
			Pimpl<Impl> pimpl;
		};
	}
}
