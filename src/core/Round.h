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

			void addPlayerTurn(const std::shared_ptr<PlayerTurn>& x);
			std::vector<std::shared_ptr<PlayerTurn>> getPlayerTurns() const;

		private:
			std::vector<std::shared_ptr<PlayerTurn>> playerTurns;
		};
	}
}
