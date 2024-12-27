//
// Created by Сергей Перлин on 03.12.2024.
//

#ifndef DRIVERCONTROLLER_H
#define DRIVERCONTROLLER_H

#include <QSqlDatabase>
#include <QVector>
#include <QSettings>
#include <QSqlError>
#include <QSqlQuery>
#include <QSharedPointer>
#include <QDebug>
#include <QRegularExpression>

#include "../Entities/Driver.h"
#include "../Exceptions/CustomExceptions.h"

class DriverController {
public:
    static void validateDriver(const Driver& driver);
    static QVector<QSharedPointer<Driver>> all(const QString& by = "name", bool desc = false);
    static int add(const QString& name, int  age, int team_id);
    static void update(int id, const QString& name, int age, int team_id);
    static QSharedPointer<Driver> getById(int id);

    static void removeDriverFromRace(int driverId, int raceId);

    static void remove(int id);

    static QVector<QSharedPointer<Driver>> getDriversByTeamId(uint id);

    static QVector<QSharedPointer<Driver>> getDriversByRaceId(uint raceId);

    static int getDriverPointsInRace(int driverId, int raceId);

    static QSharedPointer<Driver> getDriverByNameAndTeam(const QString &name, const QString &teamName);

    static void addDriverToRace(int driverId, int raceId, int points);

private:
    static QSqlQuery prepareAndExecQuery(const QString &queryStr, const QVariantMap &bindValues);
    static QSqlDatabase getDatabase();
};


#endif //DRIVERCONTROLLER_H
