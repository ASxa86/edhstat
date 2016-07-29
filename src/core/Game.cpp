#include <core/Game.h>
#include <core/PimplImpl.h>

using namespace edh::core;

class Game::Impl
{
	public:
		Impl()
		{
		}
};

Game::Game(const std::string& id) : Object(id),
	pimpl()
{
}

Game::~Game()
{
}
