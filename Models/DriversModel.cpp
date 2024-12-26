

DriversModel::DriversModel(QObject* parent)
        : QAbstractListModel(parent) {}

int DriversModel::rowCount(const QModelIndex &parent) const {
    return m_drivers.length();
}

QVariant DriversModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() < 0 || index.row() >= m_drivers.size())
        return QVariant();
    const auto& driver = m_drivers.at(index.row());
    switch(role) {
        qDebug() << "Role: " << role;
        case IdRole:
            qDebug() << "IdRole: " << driver->id();
            return driver->id();
        case NameRole: return driver->name();
        case AgeRole: return driver->age();
        case TeamRole: return driver->team();
        case PointsRole: return driver->points();
        case Qt::DisplayRole: return driver->name();
        default:
            return QVariant();
    }
}

QHash<int, QByteArray> DriversModel::roleNames() const {
    QHash<int, QByteArray> roles;

    roles[IdRole] = "id";
    roles[NameRole] = "name";
    roles[AgeRole] = "age";
    roles[TeamRole] = "team";
    roles[PointsRole] = "points";

    return roles;

}

void DriversModel::addDriver(QSharedPointer<Driver> driver) {
    beginInsertRows(QModelIndex(), m_drivers.size(), m_drivers.size());
    m_drivers.push_back(driver);
    endInsertRows();

    qDebug() << "Driver added: " << driver->name();
}

void DriversModel::clearDrivers() {
    beginResetModel();
    m_drivers.clear();
    endResetModel();
}


int DriversModel::findDriverRow(int driverId) const {
    for (int i = 0; i < rowCount(); ++i) {
        if (data(index(i), IdRole).toInt() == driverId) {
            return i;
        }
    }
    return -1; // Если гонщик не найден
}

void DriversModel::updateDriver(int row, QSharedPointer<Driver> driver) {
    if (row < 0 || row >= rowCount()) return;

    // Обновляем данные в модели
    m_drivers[row] = driver;
    emit dataChanged(index(row), index(row));
}

void DriversModel::removeDriver(int row) {
    if (row < 0 || row >= rowCount()) return;

    beginRemoveRows(QModelIndex(), row, row);
    m_drivers.removeAt(row);
    endRemoveRows();
}

