//
// Created by Сергей Перлин on 07.11.2024.
//

#include "DriverListModel.h"

DriverListModel::DriverListModel(QObject *parent) : QAbstractListModel(parent){}

void DriverListModel::setDrivers(const QVector<Driver>& drivers) {
    beginResetModel();
    m_drivers = drivers;
    endResetModel();
}

QVariant DriverListModel::data(const QModelIndex &index, int role) const {
    if(!index.isValid() && index.row() >= m_drivers.size()) {
        return QVariant();
    }

    const Driver &curDriver = m_drivers[index.row()];
    switch(role) {
        case NameRole:
            return curDriver.getName();
        case AgeRole:
            return curDriver.getAge();
        case TeamRole:
            return curDriver.getTeam();
        case PointsRole:
            return curDriver.getPoints();
        default: return QVariant();
    }


}

int DriverListModel::rowCount(const QModelIndex &parent) const{
    return m_drivers.size();
}


QHash<int, QByteArray> DriverListModel::roleNames() const  {
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[AgeRole] = "age";
    roles[TeamRole] = "team";
    roles[PointsRole] = "points";
    return roles;
}