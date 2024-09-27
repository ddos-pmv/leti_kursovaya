//
// Created by Сергей Перлин on 27.09.2024.
//

#ifndef DRIVERMODEL_H
#define DRIVERMODEL_H


#include "IModel.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>

#include "./../Entities/Driver.h"


class DriverModel : public IModel<Driver> {
private:
    QSqlDatabase &db;

    // Driver* getByName(const QString &name) {
    //     QSqlQuery query(db);
    //     query.prepare("SELECT * FROM DRIVERS WHERE name = ?");
    //     query.addBindValue(name);
    //
    //     if(query.exec() && query.next()) {
    //         return new Driver(
    //             query.value(0).toString(),
    //             query.value(1).toInt(),
    //             query.value(2).toString(),
    //             query.value(3).toInt()
    //             );
    //     }
    //     return nullptr;
    // }

public:
    DriverModel(QSqlDatabase &db) : db(db) {};

    bool add(const Driver &driver) {
        // Driver * tmpDriver = getByName(driver.getName())
        // if(tmpDriver != nullptr) {
        //     qDebug() << "Driver already exists";
        //     delete
        // }

        QSqlQuery query(db);
        query.prepare("INSERT INTO DRIVERS (name, age, team, points) VALUES (?, ?, ?, ?)");

        query.addBindValue(driver.getName());
        query.addBindValue(driver.getAge());
        query.addBindValue(driver.getTeam());
        query.addBindValue(driver.getPoints());

        if(!query.exec()) {
            qDebug() <<  "Error adding driver " << query.lastError().text();
            return false;
        }
        return true;
    }

    bool remove(int id) override {
        QSqlQuery query(db);
        query.prepare("DELETE FROM DRIVERS WHERE ID = ?");
        query.addBindValue(id);
        return query.exec();
    }

    Driver* getById(int id) override {
        QSqlQuery query(db);
        query.prepare("SELECT id, name, age, team, points FROM Drivers WHERE id = ?");
        query.addBindValue(id);
        if(query.exec() && query.next()) {
            return  new Driver(
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



};

#endif //DRIVERMODEL_H
