#pragma once

#include <core/Pimpl.h>
#include <qt/Export.h>
#include <QtWidgets/QStyledItemDelegate>

namespace edh
{
	namespace core
	{
		class Game;
	}

	namespace qt
	{
		///
		///	\class DelegateTurnActionType
		///
		///	\brief A delegate for providing editing to the
		///
		class EDHQT_EXPORT DelegatePlayer : public QStyledItemDelegate
		{
			Q_OBJECT

		public:
			DelegatePlayer(QObject* parent = nullptr);
			~DelegatePlayer() override;
			QString displayText(const QVariant& value, const QLocale& locale) const override;
			QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
			void setEditorData(QWidget* editor, const QModelIndex& index) const override;
			void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;

			void setGame(const std::shared_ptr<edh::core::Game>& x);

		protected:
			void commitAndCloseEditor();

		private:
			struct Impl;
			Pimpl<Impl> pimpl;
		};
	}
}
