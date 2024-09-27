//
// Created by Сергей Перлин on 27.09.2024.
//

#ifndef TRACKMODEL_H
#define TRACKMODEL_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include "IModel.h"
#include "./../Entities/Track.h"

class TrackModel : public IModel<Track> {
private:
    QSqlDatabase &db;

public:
    TrackModel(QSqlDatabase &db) : db(db) {};

    bool add(const Track &track) override {
        QSqlQuery query(db);
        query.prepare("INSERT INTO Tracks (name, location) VALUES (?, ?)");
        query.addBindValue(track.getName());
        query.addBindValue(track.getLocation());

        if(!query.exec()) {
            qDebug() << "Error adding track: " << query.lastError().text();
            return false;
        }
        return true;
    }

    bool remove(int trackId) override {
        QSqlQuery query(db);
        query.prepare("DELETE FROM Tracks WHERE id = ?");
        query.addBindValue(trackId);

        return query.exec();
    }

    Track *getById(int trackId) override {
        QSqlQuery query(db);
        query.prepare("SELECT id, name, location FROM Tracks WHERE id = ?");

        if (query.exec() && query.next()) {
            return new Track(query.value(0).toInt(),
                             query.value(1).toString(),
                             query.value(2).toString());
        }

        return nullptr;
    }
};

#endif //TRACKMODEL_H
