#pragma once

#include <core/Pimpl.h>
#include <qt/Export.h>
#include <QtCore/QAbstractTableModel>

namespace edh
{
	namespace core
	{
		class Game;
		class Player;
	}

	namespace qt
	{
		class EDHQT_EXPORT PlayerTableModel : public QAbstractTableModel
		{
			Q_OBJECT

		public:
			enum Column : int
			{
				Name,
				LifeTotal,
				PoisonCounters,
				ExperienceCounters,
				Count
			};

			PlayerTableModel(const std::shared_ptr<edh::core::Game>& game, QObject* parent = nullptr);
			virtual ~PlayerTableModel() override;

			virtual int columnCount(const QModelIndex& index = QModelIndex()) const override;
			virtual int rowCount(const QModelIndex& index = QModelIndex()) const override;

			virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
			virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
			virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
			virtual Qt::ItemFlags flags(const QModelIndex& index) const override;

		private:
			struct Impl;
			Pimpl<Impl> pimpl;
		};
	}
}
