//
// Created by Сергей Перлин on 07.11.2024.
//

#ifndef DRIVERLISTMODEL_H
#define DRIVERLISTMODEL_H
#include <QAbstractListModel>
#include "Entities/Driver.h"

class DriverListModel : public QAbstractListModel {
    Q_OBJECT
private:
    QVector<Driver> m_drivers;
public:
    DriverListModel(QObject *parent = nullptr);
    enum DriverRoles {
        NameRole =  Qt::UserRole + 1,
        AgeRole,
        TeamRole,
        PointsRole
    };
    void setDrivers(const QVector<Driver>& drivers);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QHash<int, QByteArray> roleNames() const override;


};


#endif //DRIVERLISTMODEL_H
