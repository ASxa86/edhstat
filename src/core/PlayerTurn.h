#pragma once

#include <core/Export.h>
#include <functional>
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
			PlayerTurn(const Player& x);
			~PlayerTurn();

			///
			///	\brief Return the player for which this turn belongs to.
			///
			const Player& getPlayer() const;

			void addTurnAction(const TurnAction& x);
			const std::vector<TurnAction>& getTurnAction() const;

		private:
			std::vector<TurnAction> turnActions;
			std::reference_wrapper<const Player> player;
		};
	}
}
