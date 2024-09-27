// mechanic.h
#ifndef MECHANIC_H
#define MECHANIC_H

#include "Person.h"
#include <QString>

class Mechanic : public Person {
private:
    QString speciality;

public:
    Mechanic(int id, const QString &name, uint age, const QString &team, const QString &speciality)
        : Person(id, name, age, team), speciality(speciality) {};

    Mechanic(const QString &name, uint age, const QString &team, const QString &speciality)
        : Person(-1, name, age, team), speciality(speciality) {};

    //Getters
    QString getSpeciality() const {return speciality;}

    // Сеттеры
    void setSpeciality(const QString &speciality) { this->speciality = speciality; }
};

#endif // MECHANIC_H
