#include "DriverModel.h"

QVector<Driver> DriverModel::getAllSortedByName() {
    QSqlDatabase database = QSqlDatabase::database(qgetenv("DB_CONNECTION_STRING"));
    if (!database.isOpen()) {
        qDebug() << "Error: Database not open for getting all drivers!";
        return {};
    }

    QSqlQuery query(database);
    query.prepare("SELECT * FROM Drivers ORDER BY name");

    QVector<Driver> drivers;

    if (query.exec()) {
        while (query.next()) {
            drivers.append(Driver(
                query.value(0).toInt(),
                query.value(1).toString(),
                query.value(2).toInt(),
                query.value(3).toString(),
                query.value(4).toInt()
            ));
        }
    } else {
        qDebug() << "Error getting drivers: " << query.lastError().text();
    }

    return drivers;
}


QVector<Driver> DriverModel::getAllSortedByPoints() {
    QSqlDatabase database = QSqlDatabase::database(qgetenv("DB_CONNECTION_STRING"));
    if (!database.isOpen()) {
        qDebug() << "Error: Database not open for getting all drivers!";
        return {};
    }

    QSqlQuery query(database);
    query.prepare("SELECT * FROM Drivers ORDER BY points");

    QVector<Driver> drivers;

    if (query.exec()) {
        while (query.next()) {
            drivers.append(Driver(
                query.value(0).toInt(),
                query.value(1).toString(),
                query.value(2).toInt(),
                query.value(3).toString(),
                query.value(4).toInt()
            ));
        }
    } else {
        qDebug() << "Error getting drivers: " << query.lastError().text();
    }

    return drivers;
}

QVector<Driver> DriverModel::getByName(const QString &name) {
    QSqlDatabase database = QSqlDatabase::database(qgetenv("DB_CONNECTION_STRING"));
    if (!database.isOpen()) {
        qDebug() << "Error: Database not open for getting drivers by name!";
        return {};
    }

    QSqlQuery query(database);
    query.prepare("SELECT * FROM Drivers WHERE name = ?");
    query.addBindValue(name);

    QVector<Driver> drivers;

    if (query.exec()) {
        while (query.next()) {
            drivers.append(Driver(
                query.value(0).toInt(),
                query.value(1).toString(),
                query.value(2).toInt(),
                query.value(3).toString(),
                query.value(4).toInt()
            ));
        }
    } else {
        qDebug() << "Error getting drivers by name: " << query.lastError().text();
    }

    return drivers;
}