//
// Created by Сергей Перлин on 06.12.2024.
//

#ifndef TEAM_H
#define TEAM_H

#include <QString>
#include <QObject>

class Team : public QObject{
    int m_id;
    QString m_name;
    int m_driversCol;
    int m_pointsSum;
public:

    Team(int id, const QString& name, int drivers = 0, int pointsSum = 0, QObject* parent = nullptr);
    Team(const QString& name, int drivers = 0, int pointsSum = 0, QObject* parent = nullptr);

    uint id() const;
    QString name() const;
    int driversCol() const;
    int pointsSum() const;

    void setId(int id);
    void setName(const QString& teamName);
    void setDriversCol(int driversCol);
    void setPointsSum(int pointsSum);

};

#endif //TEAM_H
