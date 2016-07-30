#pragma once

#include <QtWidgets/QMainWindow>
#include <core/Pimpl.h>

namespace edh
{
	class FormMain : public QMainWindow
	{
		Q_OBJECT

		public:
			FormMain(QWidget* parent = nullptr);
			~FormMain() override;

		private:
			class Impl;
			Pimpl<Impl> pimpl;
	};
}
