#pragma once

#include <core/Export.h>
#include <memory>
#include <chrono>
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

			void addPlayer(const std::shared_ptr<Player>& x);
			void insertPlayer(size_t index, const std::shared_ptr<Player>& x);
			void removePlayer(const std::shared_ptr<Player>& x);
			std::vector<std::shared_ptr<Player>> getPlayers() const;

			void addRound(const std::shared_ptr<Round>& x);
			std::vector<std::shared_ptr<Round>> getRounds() const;

			void setTime(std::chrono::duration<double> x);
			std::chrono::duration<double> getTime() const;

		private:
			std::vector<std::shared_ptr<Player>> players;
			std::vector<std::shared_ptr<Round>> rounds;
			std::chrono::duration<double> time;
		};
	}
}
