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

#include "../Entities/Driver.h"
#include "../Exceptions/CustomExceptions.h"

class DriverController {
private:
public:
    static void validateDriver(const Driver& driver);
    static QVector<Driver> all(const QString& by = "name", bool desc = false);
    static void add(const QString& name, int  age, int team_id);
    static void update(int id, const QString& name, int age, int team_id);

};


#endif //DRIVERCONTROLLER_H
