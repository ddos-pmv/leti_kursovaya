//
// Created by Сергей Перлин on 27.09.2024.
//

#ifndef TRACK_H
#define TRACK_H
#include <QString>

class Track {
private:
    int id;
    QString name;
    QString location;
public:
    Track(int id, const QString &name, const QString &location)
        : id(id), name(name), location(location) {};
    Track(const QString &name, const QString &location)
        : id(-1), name(name), location(location) {};

    // Getters
    int getId() const {return id;}
    QString getName() const {return name;}
    QString getLocation() const {return location;}


    // Setters
    void setName(const QString &name) { this->name = name; }




};


#endif //TRACK_H
