#include <QSqlDatabase>
#include <QApplication>
#include <QDebug>
#include "Models/DriverModel.h"
#include "Entities/Driver.h"

int main (int argc, char *argv[]) {
    QApplication app(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("racing.db");

    if(!db.open()) {
        qDebug() << "Error opening database" << db.lastError().text();
        return -1;
    }

    qDebug() << "Opened database";

    DriverModel driverModel(db);




    Driver driver("Lewis Hamilton", 36, "Mercedes", 250);
    driverModel.add(driver);



    return app.exec();
}
