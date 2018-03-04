#pragma once

#include <core/Export.h>
#include <chrono>
#include <functional>
#include <memory>
#include <vector>

namespace edh
{
	namespace core
	{
		class Player;
		class TurnAction;

		///
		///	\class Turn
		///
		///	\brief This class represents and manages a single player's turn.
		///
		///	\date February 28, 2018
		///
		///	\author Aaron Shelley
		///
		class EDHCORE_EXPORT PlayerTurn
		{
		public:
			PlayerTurn() = delete;
			PlayerTurn(const std::shared_ptr<Player>& x);
			~PlayerTurn();

			///
			///	\brief Return the player for which this turn belongs to.
			///
			std::shared_ptr<Player> getPlayer() const;

			void addTurnAction(const std::shared_ptr<TurnAction>& x);
			std::vector<std::shared_ptr<TurnAction>> getTurnAction() const;

			void setTime(std::chrono::duration<double> x);
			std::chrono::duration<double> getTime() const;

		private:
			std::vector<std::shared_ptr<TurnAction>> turnActions;
			std::weak_ptr<Player> player;
			std::chrono::duration<double> time;
		};
	}
}
