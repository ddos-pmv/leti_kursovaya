//
// Created by Сергей Перлин on 03.12.2024.
//

// Driver.h
#ifndef DRIVER_H
#define DRIVER_H

#include <QObject>

class Driver : public QObject {
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(int age READ age WRITE setAge NOTIFY ageChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString team READ team WRITE setTeam NOTIFY teamChanged)
    Q_PROPERTY(int points READ points WRITE setPoints NOTIFY pointsChanged)
public:
    Driver(int id, const QString &name, uint age, const QString &team, int points = 0, QObject* parent = nullptr)
    : m_id(id), m_name(name), m_age(age), m_team(team), m_points(points), QObject(parent) {};
    Driver(const QString &name, uint age, const QString &team, int points = 0, QObject* parent = nullptr) noexcept
        : m_id(-1), m_name(name), m_age(age), m_team(team), m_points(points), QObject(parent){};

    int id() const {return m_id;}
    int age() const {return m_age;}
    QString name() const {return m_name;}
    QString team() const {return m_team;}
    int points() const {return m_points;}

    void setId(int id) {
        if(m_id != id){
            m_id = id;
            emit idChanged(m_id);
        }
    }
    void setName(const QString& name) {
        if(m_name != name) {
            m_name = name;
            emit nameChanged(m_name);
        }
    }

    void setAge(int age) {
        if(m_age != age) {
            m_age = age;
            emit ageChanged(m_age);
        }
    }


    void setTeam(const QString& team) {
        if(m_team != team) {
            m_team = team;
            emit teamChanged(m_team);
        }
    }

    void setPoints(int points) {
        m_points = points;
        emit pointsChanged(m_points);
    }


signals:
    void idChanged(int);
    void teamChanged(const QString&);
    void nameChanged(const QString&);
    void ageChanged(int);
    void pointsChanged(int);


private:
    int m_id;
    QString m_name;
    int m_age;
    QString m_team;
    int m_points;
};


#endif //DRIVER_H
