#include <core/Game.h>
#include <core/PimplImpl.h>

#include <logger/Logger.h>

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
