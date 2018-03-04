#pragma once

#include <core/Pimpl.h>
#include <qt/Export.h>
#include <QtWidgets/QTreeWidget>

namespace edh
{
	namespace core
	{
		class Game;
	}

	namespace qt
	{
		class EDHQT_EXPORT TreeWidgetRounds : public QTreeWidget
		{
			Q_OBJECT

		public:
			TreeWidgetRounds(QWidget* parent = nullptr);
			~TreeWidgetRounds();

			void setGame(const std::shared_ptr<edh::core::Game>& x);

		private:
			struct Impl;
			Pimpl<Impl> pimpl;
		};
	}
}
