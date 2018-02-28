#pragma once

#include <core/Export.h>
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
		class EDHCORE_EXPORT Player
		{
		public:
			Player();
			~Player();

			void setName(const std::string& x);
			std::string getName() const;

			void setLifeTotal(int x);
			int getLifeTotal() const;

			void setPoisonCounters(int x);
			int getPoisonCounters() const;

			void setExperienceCounters(int x);
			int getExperienceCounters();

		private:
			std::string name;
			int lifeTotal;
			int poisonCounters;
			int experienceCounters;
		};
	}
}
