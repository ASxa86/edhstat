#pragma once

#include <core/Pimpl.h>
#include <QtWidgets/QMainWindow>

namespace edh
{
	class MainWindow : public QMainWindow
	{
		Q_OBJECT
			
	public:
		MainWindow(QWidget* parent = nullptr);
		~MainWindow();

	protected:
		void initializeMenuFile();
		void initializeMenuEdit();

	private:
		struct Impl;
		Pimpl<Impl> pimpl;
	};
}
