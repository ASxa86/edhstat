#pragma once

#include <core/Pimpl.h>
#include <qt/Export.h>
#include <QtWidgets/QWidget>

namespace edh
{
	namespace core
	{
		class Game;
	}

	namespace qt
	{
		class EDHQT_EXPORT WidgetPlayers : public QWidget
		{
			Q_OBJECT

		public:
			WidgetPlayers(QWidget* parent = nullptr);
			~WidgetPlayers();

			void setGame(const std::shared_ptr<edh::core::Game>& x);

			void clear();

		private:
			struct Impl;
			Pimpl<Impl> pimpl;
		};
	}
}
