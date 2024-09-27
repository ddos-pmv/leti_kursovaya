//
// Created by Сергей Перлин on 27.09.2024.
//

#ifndef PERSON_H
#define PERSON_H

#include <QString>

class Person {
protected:
    int id;
    QString name;
    uint age;
    QString team;

public:
    Person(int id, const QString &name, uint age, const QString &team)
        : id(id), name(name), age(age), team(team){};

    //Getterss
    QString getName() const {return name;}
    QString getTeam() const {return team;}
    uint getAge() const {return age;}

    //Setters
    void setName(const QString &newName) { name = newName; }
    void setAge(int newAge) { age = newAge; }
    void setTeam(const QString &newTeam) { team = newTeam; }

    virtual QString getInfo() const = 0;
};

#endif //PERSON_H
