#pragma once

#include <core/Object.h>

namespace edh
{
	namespace core
	{
		///
		///	\class Game
		///
		///	\brief This class maintains the state of the entire game.
		///
		///	This class will manage the game's clock among other states
		///
		///	\date July 28, 2016
		///
		///	\author Aaron Shelley
		///
		class EDHCORE_EXPORT Game : public Object
		{
			public:
				Game(const std::string& id = "edh::core::Game");
				~Game() override;

			private:
				class Impl;
				Pimpl<Impl> pimpl;
		};
	}
}
