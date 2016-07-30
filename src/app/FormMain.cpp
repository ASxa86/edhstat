#include <app/FormMain.h>
#include <core/PimplImpl.h>

#include <core/Game.h>

using namespace edh;
using namespace edh::core;

class FormMain::Impl
{
	public:
		Impl()
		{
		}
};

FormMain::FormMain(QWidget* parent) : QMainWindow(parent),
	pimpl()
{
	Game game;
}

FormMain::~FormMain()
{
}
