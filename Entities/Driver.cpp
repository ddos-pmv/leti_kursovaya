#include "Driver.h"

Driver::Driver(int id, const QString &name, uint age, const QString &team, int points, QObject* parent)
: m_id(id), m_name(name), m_age(age), m_team(team), m_points(points), QObject(parent) {};

Driver::Driver(const QString &name, uint age,const QString &team, int points, QObject* parent) noexcept
    : m_id(-1), m_name(name), m_age(age),m_team(team),
    m_points(points), QObject(parent){};

int Driver::id() const {return m_id;}
int Driver::age() const {return m_age;}
QString Driver::name() const {return m_name;}
QString Driver::team() const {return m_team;}
int Driver::points() const {return m_points;}

void Driver::setId(int id) {
    if(m_id != id){
        m_id = id;
        emit idChanged(m_id);
    }
}

void Driver::setName(const QString& name) {
    if(m_name != name) {
        m_name = name;
        emit nameChanged(m_name);
    }
}

void Driver::setAge(int age) {
    if(m_age != age) {
        m_age = age;
        emit ageChanged(m_age);
    }
}

void Driver::setTeam(const QString& team) {
    if(m_team != team) {
        m_team = team;
        emit teamChanged(m_team);
    }
}

void Driver::setPoints(int points) {
    m_points = points;
    emit pointsChanged(m_points);
}



