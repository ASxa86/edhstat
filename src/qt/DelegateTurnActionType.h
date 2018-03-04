#pragma once

#include <qt/Export.h>
#include <QtWidgets/QStyledItemDelegate>

namespace edh
{
	namespace qt
	{
		///
		///	\class DelegateTurnActionType
		///
		///	\brief A delegate for providing editing to the
		///
		class EDHQT_EXPORT DelegateTurnActionType : public QStyledItemDelegate
		{
			Q_OBJECT

		public:
			DelegateTurnActionType(QObject* parent = nullptr);
			~DelegateTurnActionType() override;
			QString displayText(const QVariant& value, const QLocale& locale) const override;
			QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
			void setEditorData(QWidget* editor, const QModelIndex& index) const override;
			void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;

		protected:
			void commitAndCloseEditor();
		};
	}
}
