#pragma once

#include <core/Pimpl.h>
#include <qt/Export.h>
#include <QtCore/QObject>

namespace edh
{
	namespace qt
	{
		class GroupBoxPlayer;

		///
		///	\class GroupBoxPlayerGroup
		///
		///	\brief Similar to a QButtonGroup, this manages the toggle state of multiple player group boxes.
		///
		///	\date March 5, 2018
		///
		///	\author Aaron Shelley
		///
		class EDHQT_EXPORT GroupBoxGroup : public QObject
		{
			Q_OBJECT

		public:
			GroupBoxGroup(QObject* parent = nullptr);
			~GroupBoxGroup();

			void addGroupBox(GroupBoxPlayer* x);
			void removeGroupBox(GroupBoxPlayer* x);

			void setCheckedGroupBox(GroupBoxPlayer* x);
			GroupBoxPlayer* getCheckedGroupBox() const;

		signals:
			void groupBoxToggled(GroupBoxPlayer*, bool checked);

		private:
			struct Impl;
			Pimpl<Impl> pimpl;
		};
	}
}
