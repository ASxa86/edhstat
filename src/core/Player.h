#pragma once

#include <core/Dirty.h>
#include <core/Export.h>
#include <core/Pimpl.h>
#include <chrono>
#include <functional>
#include <string>

namespace edh
{
	namespace core
	{
		///
		///	\class Player
		///
		///	\brief This class represents and manages a player in a game of EDH.
		///
		///	\date February 27, 2018
		///
		///	\author Aaron Shelley
		///
		class EDHCORE_EXPORT Player : public Dirty<Player>
		{
		public:
			Player(const std::string& x = std::string());
			~Player();

			void setName(const std::string& x);
			std::string getName() const;

			void setLifeTotal(int x);
			int getLifeTotal() const;

			void setPoisonCounters(int x);
			int getPoisonCounters() const;

			void setExperienceCounters(int x);
			int getExperienceCounters();

			void setTurnTime(std::chrono::duration<double> x);
			std::chrono::duration<double> getTurnTime() const;

		private:
			struct Impl;
			Pimpl<Impl> pimpl;
		};
	}
}
