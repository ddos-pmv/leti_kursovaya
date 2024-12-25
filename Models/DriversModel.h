//
// Created by Сергей Перлин on 23.12.2024.
//

#ifndef DIRVERSMODEL_H
#define DIRVERSMODEL_H

#include <QAbstractListModel>
#include <QVector>
#include <QSharedPointer>
#include <QDebug>

#include "../Entities/Driver.h"



class DriversModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum DriverRoles {
        IdRole =  Qt::UserRole+1,
        NameRole,
        AgeRole,
        TeamRole,
        PointsRole
    };

    explicit DriversModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void addDriver(QSharedPointer<Driver> driver);
    void clearDrivers();

    int findDriverRow(int driverId) const;

    void updateDriver(int row, QSharedPointer<Driver> driver);

    void removeDriver(int row);

private:
    QVector<QSharedPointer<Driver>> m_drivers;


};



#endif //DIRVERSMODEL_H
