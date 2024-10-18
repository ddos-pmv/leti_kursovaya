// driver.h
#ifndef DRIVER_H
#define DRIVER_H

#include "Person.h"
#include <QString>

class Driver : public Person {
private:
    int points;

public:
    Driver(int id, const QString &name, uint age, const QString &team, int points)
        : Person(id, name, age, team), points(points) {};
    Driver(const QString &name, uint age, const QString &team, int points)
        : Person(-1, name, age, team), points(points) {};

    //Getters
    int getPoints() const { return points; }

    // Сеттеры
    void setPoints(int newPoints) { points = newPoints; }
    void setId(int id) {this->id = id;}

    QString getInfo() const override {
        return QString("Driver: %1, Team: %2, Points: %3").arg(name, team).arg(points);
    }
};

#endif // DRIVER_H
