//
// Created by Сергей Перлин on 27.09.2024.
//

#ifndef TEAMMANAGER_H
#define TEAMMANAGER_H

#include "Person.h"
#include <QString>

class TeamManager : public Person {
private:
    uint experience = 0;

public:
    TeamManager(int id, const QString &name, uint age, const QString &team, uint experience = 0)
        : Person(id, name, age, team), experience(experience) {};
    TeamManager(const QString &name, uint age, const QString &team, uint experience = 0)
        : Person(-1, name, age, team), experience(experience) {};

    // Getters
    uint getExperience() const {return experience;}

    // Setters
    void setExperience(uint exp) { this->experience = exp; }
};

#endif //TEAMMANAGER_H
