#include <qt/DialogPlayerConfiguration.h>

#include <core/PimplImpl.h>
#include <core/Game.h>
#include <core/Player.h>
#include <qt/WidgetPlayerTable.h>
#include <QtWidgets/QBoxLayout>

using namespace edh::core;
using namespace edh::qt;

struct DialogPlayerConfiguration::Impl
{
	std::weak_ptr<Game> game;

	WidgetPlayerTable* wPlayerTable{nullptr};
};

DialogPlayerConfiguration::DialogPlayerConfiguration(QWidget* parent) : QDialog(parent), pimpl()
{
	const auto layout = new QVBoxLayout(this);
	layout->setMargin(0);

	this->pimpl->wPlayerTable = new WidgetPlayerTable();
	layout->addWidget(this->pimpl->wPlayerTable);
}

DialogPlayerConfiguration::~DialogPlayerConfiguration()
{
}

void DialogPlayerConfiguration::setGame(const std::shared_ptr<edh::core::Game>& x)
{
	this->pimpl->game = x;

	if(x != nullptr)
	{
		this->pimpl->wPlayerTable->setGame(x);
	}
}
