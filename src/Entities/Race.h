//
// Created by Сергей Перлин on 28.09.2024.
//

#ifndef RACE_H
#define RACE_H

#include <QString>

class Race {
private:
    int id;
    int track_id;
    QString date;

public:
    Race(int id, int track_id, const QString &date)
        : id(id), track_id(track_id), date(date) {};
    Race(int track_id, const Qstring &date)
        : id(-1), track_id(track_id), date(date) {};

    // Getters
    int getId() const {return id;}
    int getTrackId() const {return track_id;}
    QString getDate() const {return date;}

    // Setters
    void setDate(const QStringg &date) {this->date = date;}
};


#endif //RACE_H
