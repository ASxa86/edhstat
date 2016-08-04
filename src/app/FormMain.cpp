#include <app/FormMain.h>
#include <core/PimplImpl.h>

using namespace edh;

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
}

FormMain::~FormMain()
{
}
