#pragma once

#include <core/Export.h>
#include <core/Pimpl.h>
#include <chrono>
#include <functional>
#include <memory>
#include <vector>

namespace boost
{
	namespace signals2
	{
		class connection;
	}
}

namespace edh
{
	namespace core
	{
		class connection;
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
			int indexOfPlayer(const std::shared_ptr<Player>& x) const;
			std::vector<std::shared_ptr<Player>> getPlayers() const;

			void addRound(const std::shared_ptr<Round>& x);
			std::shared_ptr<Round> getCurrentRound() const;
			std::vector<std::shared_ptr<Round>> getRounds() const;

			void setTime(std::chrono::duration<double> x);
			std::chrono::duration<double> getTime() const;

			boost::signals2::connection addAddPlayerObserver(const std::function<void(std::shared_ptr<Player>)>& x);
			boost::signals2::connection addRemovePlayerObserver(const std::function<void(std::shared_ptr<Player>)>& x);

		private:
			struct Impl;
			Pimpl<Impl> pimpl;
		};
	}
}
