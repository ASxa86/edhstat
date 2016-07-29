#pragma once

#include <core/Object.h>

namespace edh
{
	namespace core
	{
		///
		///	\class Turn
		///
		///	\brief This class represents a single player's turn.
		///
		///	A turn can consist of how long the turn took, the delta of a player's state, etc.
		///
		///	\date July 28, 2016
		///
		///	\author Aaron Shelley
		///
		class EDHCORE_EXPORT Turn : public Object
		{
			public:
				Turn(const std::string& id);
				~Turn() override;

				void setTime(double x);
				double getTime() const;

				void setLifeTotalDelta(int x);
				int getLifeTotalDelta() const;

				void setPoisonCounterDelta(std::size_t x);
				std::size_t getPoisonCounterDelta() const;

				void setExperienceCounterDelta(std::size_t x);
				std::size_t getExperienceCounterDelta() const;

			private:
				class Impl;
				Pimpl<Impl> pimpl;
		};
	}
}
