//
// Created by Сергей Перлин on 28.09.2024.
//

#ifndef RACEMODEL_H
#define RACEMODEL_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include "./../Entities/Race.h"
#include "IModel.h"

class RaceModel : public IModel<Race> {
private:
    QSqlDatabase &db;

public:
    RaceModel(QSqlDatabase &db) : db(db) {};

    bool add(const Race &race) override {
        QSqlQuery query(db);
        query.prepare("INSERT INTO Races (track_id, date) VALUES (?, ?)");
        query.addBindValue(race.getTrackId());
        query.addBindValue(race.getDate());

        if (!query.exec()) {
            qDebug() << "Error adding race: " << query.lastError().text();
            return false;
        }

        return true;
    }

    Race* getById(int id) override {
        QSqlQuery query(db);
        query.prepare("SELECT id, track_id, date FROM Races WHERE id = ?");
        query.addBindValue(id);

        if (query.exec() && query.next()) {
            return new Race(query.value(0).toInt(),
                            query.value(1).toInt(),
                            query.value(2).toString());
        }

        return nullptr;
    }

    bool remove(int id) override {
        QSqlQuery query(db);
        query.prepare("DELETE FROM Races WHERE id = ?");
    }
};


#endif //RACEMODEL_H
