#pragma once

#include <core/Pimpl.h>
#include <qt/Export.h>
#include <QtWidgets/QTableWidget>

namespace edh
{
	namespace core
	{
		class Game;
	}

	namespace qt
	{
		class EDHQT_EXPORT WidgetPlayerTable : public QTableWidget
		{
			Q_OBJECT

		public:
			WidgetPlayerTable(QWidget* parent = nullptr);
			~WidgetPlayerTable() override;

			void setGame(const std::shared_ptr<edh::core::Game>& x);

		private:
			struct Impl;
			Pimpl<Impl> pimpl;
		};
	}
}
