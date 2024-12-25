//
// Created by Сергей Перлин on 03.12.2024.
//

// Driver.h
#ifndef DRIVER_H
#define DRIVER_H

#include "IPerson.h"

class Driver : public IPerson {
private:
    int m_points;

public:
    Driver(int id, const QString &name, uint age, const QString &team, int points = 0)
        : IPerson(id, name, age, team), m_points(points) {};
    Driver(const QString &name, uint age, const QString &team, int points = 0)
        : IPerson(-1, name, age, team), m_points(points) {};

    //Getters
    int points() const { return m_points; }

    void setPoints(int newPoints) {m_points = newPoints;}


};


#endif //DRIVER_H
