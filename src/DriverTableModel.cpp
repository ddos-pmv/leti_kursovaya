// DriverTableModel.cpp
#include "DriverTableModel.h"

DriverTableModel::DriverTableModel(QObject *parent)
    : QAbstractTableModel(parent) {}

int DriverTableModel::rowCount(const QModelIndex & /*parent*/) const {
    return m_drivers.size();
}

int DriverTableModel::columnCount(const QModelIndex & /*parent*/) const {
    return 4; // Например, колонки для имени, возраста, команды и очков
}

QVariant DriverTableModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }

    const Driver &driver = m_drivers[index.row()];
    switch (index.column()) {
        case 0: return driver.getName();
        case 1: return driver.getAge();
        case 2: return driver.getTeam();
        case 3: return driver.getPoints();
        default: return QVariant();
    }
}

void DriverTableModel::setDrivers(const QVector<Driver> &drivers) {
    beginResetModel();
    m_drivers = drivers;
    endResetModel();
}
