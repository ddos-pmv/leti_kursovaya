//
// Created by Сергей Перлин on 04.10.2024.
//

#ifndef DRIVERCONTROLLER_H
#define DRIVERCONTROLLER_H

#include "IController.h"
#include "../Entities/Driver.h"
#include "../Models/DriverModel.h"
#include <QVector>


class DriverController{

public:

    static QVector<Driver> getAllByName(){
        QVector<Driver> drivers = DriverModel::getAllSortedByName();
        for(int i = 0; i < drivers.size(); i++)
            drivers[i].setId(i);
        return drivers;
    }

    static QVector<Driver> getAllByPoints(){
        QVector<Driver> drivers = DriverModel::getAllSortedByPoints();
        for(int i = 0; i < drivers.size(); i++) drivers[i].setId(i);
        return drivers;
    }

    static Driver getByNameAndTeam(const QString &name, const QString &team){
        QVector<Driver> drivers = DriverModel::getByName(name);
        for(auto & driver : drivers){
            if(driver.getTeam() == team) {
                return driver;
            }
        }
    }
};



#endif //DRIVERCONTROLLER_H
