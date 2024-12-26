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
private:
public:
    static void validateDriver(const Driver& driver);
    static QVector<QSharedPointer<Driver>> all(const QString& by = "name", bool desc = false);
    static int add(const QString& name, int  age, int team_id);
    static void update(int id, const QString& name, int age, int team_id);
    static QSharedPointer<Driver> getById(int id);
    static void remove(int id);

};


#endif //DRIVERCONTROLLER_H
