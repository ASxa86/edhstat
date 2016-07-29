#include <qt/Widget.h>

#include <core/Game.h>

using namespace edh::qt;

edh::core::Game* edh::qt::Widget::Game = nullptr;

void edh::qt::Widget::SetGame(edh::core::Game* x)
{
	Widget::Game = x;
}

edh::core::Game* edh::qt::Widget::GetGame()
{
	return Widget::Game;
}

Widget::Widget()
{
}

Widget::~Widget()
{
}
