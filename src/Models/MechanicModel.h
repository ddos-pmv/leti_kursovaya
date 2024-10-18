//
// Created by Сергей Перлин on 27.09.2024.
//

#ifndef MECHANICMODEL_H
#define MECHANICMODEL_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include "IModel.h"
#include "./../Entities/Mechanic.h"

class MechanicMode : public IModel<Mechanic> {
private:
    QSqlDatabase db = QSqlDatabase::database(qgetenv("DB_CONNECTION_STRING"));
public:
    bool add(const Mechanic& mechanic) override {
        QSqlQuery query(db);
        query.prepare(
        "INSERT INTO MECHANICS (name, age, team, speciality)"
            "VALUES (?, ?, ?, ?)");

        query.addBindValue(mechanic.getName());
        query.addBindValue(mechanic.getAge());
        query.addBindValue(mechanic.getTeam());
        query.addBindValue(mechanic.getSpeciality());

        if(!query.exec()) {
            qDebug() << "Error adding Mechanic: " << query.lastError().text();
            return false;
        }
        return false;
    }

    Mechanic* getById(int id) override {
        QSqlQuery query(db);
        query.prepare("SELECT name, age, team, speciality FROM MECHANICS WHERE id = ?");
        query.addBindValue(id);

        if (query.exec() && query.next()) {
            return new Mechanic(
                query.value(0).toString(),
                query.value(1).toInt(),
                query.value(2).toString(),
                query.value(3).toString()
                );
        }

        qDebug() << "Error selecting Mechanic" << query.lastError().text();
        return nullptr;
    }

};

#endif //MECHANICMODEL_H
