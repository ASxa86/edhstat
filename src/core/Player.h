#pragma once

#include <core/Object.h>

namespace edh
{
	namespace core
	{
		///
		///	\class Player
		///
		///	\brief This class represents a single player in a game of EDH/Commander and maintains the player's state in the game.
		///
		///	\date July 28, 2016
		///
		///	\author Aaron Shelley
		///
		class EDHCORE_EXPORT Player : public Object
		{
			public:
				Player(const std::string& id = "edh::core::Player");
				~Player() override;

				///
				///	Set's the current life total of the player.
				///
				///	It is possible to have a negative life total and still be in the game.
				///	Such as having a platinum angel in play.
				///
				void setLifeTotal(int x);
				int getLifeTotal() const;

				void setExperienceCounters(std::size_t x);
				std::size_t getExperienceCounters() const;

				void setPoisonCounters(std::size_t x);
				std::size_t getPoisonCounters() const;

				///
				///	Sets whether 'this' player is alive.
				///	
				///	A player is considered not alive when they have lost the game whether through life
				///	reaching 0 or some other condition.
				///
				///	true - Alive and in the game
				///	false - Dead and out of the game
				///
				void setAlive(bool x);
				bool getAlive() const;

			private:
				class Impl;
				Pimpl<Impl> pimpl;
		};
	}
}
