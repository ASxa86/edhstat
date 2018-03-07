#pragma once

#include <core/Pimpl.h>
#include <qt/Export.h>
#include <QtWidgets/QDialog>

namespace edh
{
	namespace core
	{
		class Game;
	}

	namespace qt
	{
		class EDHQT_EXPORT DialogPlayerConfiguration : public QDialog
		{
			Q_OBJECT

		public:
			DialogPlayerConfiguration(QWidget* parent = nullptr);
			~DialogPlayerConfiguration() override;

			void setGame(const std::shared_ptr<edh::core::Game>& x);

		private:
			struct Impl;
			Pimpl<Impl> pimpl;
		};
	}
}
