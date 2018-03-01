#pragma once

#include <core/Export.h>
#include <vector>

namespace edh
{
	namespace core
	{
		class Player;
		class Round;

		///
		///	\class Game
		///
		///	\brief This class represents and manages a single game of EDH.
		///
		///	A game of magic consists of multiple players playing multiple turns until someone is declared a winner.
		///
		///	\date February 27, 2018
		///
		///	\authro Aaron Shelley
		///
		class EDHCORE_EXPORT Game
		{
		public:
			Game();
			~Game();

			void addPlayer(const Player& x);
			const std::vector<Player>& getPlayers() const;

			void addRound(const Round& x);
			const std::vector<Round>& getRounds() const;

		private:
			std::vector<Player> players;
			std::vector<Round> rounds;
		};
	}
}
