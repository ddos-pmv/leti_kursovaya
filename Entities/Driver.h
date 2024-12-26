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
    Driver(int id, const QString &name, uint age, const QString &team, int points = 0, QObject* parent = nullptr);
    Driver(const QString &name, uint age, const QString &team, int points = 0, QObject* parent = nullptr) noexcept;
    int id() const;
    int age() const;
    QString name() const;
    QString team() const;
    int points() const;

    void setId(int id);
    void setName(const QString& name);
    void setAge(int age);
    void setTeam(const QString& team);
    void setPoints(int points);


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
