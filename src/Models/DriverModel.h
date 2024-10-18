#ifndef DRIVERMODEL_H
#define DRIVERMODEL_H

#include "IModel.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include "./../Entities/Driver.h"

class DriverModel : public IModel<Driver> {
private:
    QSqlDatabase db;

public:
    DriverModel() {
        db = QSqlDatabase::database(qgetenv("DB_CONNECTION_STRING"));  // Получаем соединение с базой
        if (!db.isOpen()) {
            qDebug() << "Error: Database not open!";
        }
    }

    bool add(const Driver &driver) override {
        if (!db.isOpen()) {
            qDebug() << "Error: Database not open for adding driver!";
            return false;
        }

        QSqlQuery query(db);
        query.prepare("INSERT INTO DRIVERS (name, age, team, points) VALUES (?, ?, ?, ?)");

        query.addBindValue(driver.getName());
        query.addBindValue(driver.getAge());
        query.addBindValue(driver.getTeam());
        query.addBindValue(driver.getPoints());

        if (!query.exec()) {
            qDebug() << "Error adding driver: " << query.lastError().text();
            return false;
        }
        return true;
    }

    bool remove(int id) override {
        if (!db.isOpen()) {
            qDebug() << "Error: Database not open for removing driver!";
            return false;
        }

        QSqlQuery query(db);
        query.prepare("DELETE FROM DRIVERS WHERE ID = ?");
        query.addBindValue(id);

        if (!query.exec()) {
            qDebug() << "Error removing driver: " << query.lastError().text();
            return false;
        }
        return true;
    }

    Driver* getById(int id) override {
        if (!db.isOpen()) {
            qDebug() << "Error: Database not open for getting driver!";
            return nullptr;
        }

        QSqlQuery query(db);
        query.prepare("SELECT id, name, age, team, points FROM Drivers WHERE id = ?");
        query.addBindValue(id);

        if (query.exec() && query.next()) {
            return new Driver(
                query.value(0).toInt(),
                query.value(1).toString(),
                query.value(2).toInt(),
                query.value(3).toString(),
                query.value(4).toInt()
            );
        }

        qDebug() << "Error getting driver by id: " << query.lastError().text();
        return nullptr;
    }


    static QVector<Driver> getByName(const QString &name);

    static QVector<Driver> getAllSortedByName();

    static QVector<Driver> getAllSortedByPoints();
};

#endif // DRIVERMODEL_H
