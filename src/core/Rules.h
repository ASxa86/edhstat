#pragma once

#include <core/Object.h>

namespace edh
{
	namespace core
	{
		///
		///	\class Rules
		///
		///	\brief This class represents the rules for the game.
		///
		///	By default, a game of EDH has players starting at 40 life and can lose the game if 10 poison counters are reached.
		///	Having rules in place allow for custom rules configuration which can then be used to determine if a player has lost.
		///
		///	\date July 28, 2016
		///
		///	\author Aaron Shelley
		///
		class EDHCORE_EXPORT Rules : public Object
		{
			public:
				Rules(const std::string& id = "edh::core::Rules");
				~Rules() override;

				void setStartingLifeTotal(int x);
				int getStartingLifeTotal() const;

				void setPoisonCounterLimit(std::size_t x);
				std::size_t getPoisonCounterLimit() const;

			private:
				class Impl;
				Pimpl<Impl> pimpl;
		};
	}
}
