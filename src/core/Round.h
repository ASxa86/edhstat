#pragma once

#include <core/Export.h>
#include <memory>
#include <vector>

namespace edh
{
	namespace core
	{
		class PlayerTurn;

		///
		///	\class Round
		///
		///	\brief This class represents and manages a single round of magic.
		///
		///	A round of magic consists of multiple turns and ends once each player has completed their
		///	turn and the starting player's turn has begun.
		///
		///	\date February 28, 2018
		///
		///	\author Aaron Shelley
		///
		class EDHCORE_EXPORT Round
		{
		public:
			Round();
			~Round();

			///
			///	Adds a new turn to the round.
			///	This effectively sets the current turn.
			///
			void addPlayerTurn(const std::shared_ptr<PlayerTurn>& x);

			///
			///	Get the current turn for the round.
			///	This is the latest turn that has been added to the round.
			///
			std::shared_ptr<PlayerTurn> getCurrentTurn() const;

			///
			///	Retreive the list of turns for this round.
			///
			std::vector<std::shared_ptr<PlayerTurn>> getPlayerTurns() const;

		private:
			std::vector<std::shared_ptr<PlayerTurn>> playerTurns;
		};
	}
}
