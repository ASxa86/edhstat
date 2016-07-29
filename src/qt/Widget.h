#pragma once

#include <qt/Export.h>

namespace edh
{
	namespace core
	{
		class Game;
	}

	namespace qt
	{
		class EDHQT_EXPORT Widget
		{
			public:
				static void SetGame(edh::core::Game* x);
				static edh::core::Game* GetGame();

				Widget();
				virtual ~Widget();

			private:
				static edh::core::Game* Game;
		};
	}
}
