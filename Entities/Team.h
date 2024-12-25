//
// Created by Сергей Перлин on 06.12.2024.
//

#ifndef TEAM_H
#define TEAM_H

#include <QString>

class Team {
    int m_id;
    QString m_name;
    // uint m_drivers;
    // uint m_mechanics;
    // uint m_managers ;
public:
    Team(int id, const QString& name) : m_id(id), m_name(name){}
    // Team(int id, const QString& name, int drivers = 0, int mechanics = 0, int managers = 0)
    // :m_id(id), m_name(name), m_drivers(drivers), m_mechanics(mechanics), m_managers(managers) {};

    uint id() const {return m_id;}
    QString name() const {return m_name;}

};

#endif //TEAM_H
