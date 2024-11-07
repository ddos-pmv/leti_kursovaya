// main.cpp
#include <QCoreApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSqlDatabase>
#include <QApplication>
#include <QDebug>
#include <QPixmap>
#include <QScreen>

#include "Models/DriverModel.h"
#include "DriverListModel.h"
#include "Controllers/DriverController.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    qputenv("DB_CONNECTION_STRING", "my");

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "my");
    db.setDatabaseName("racing.db");



    if(!db.open()) {
        qDebug() << "Error opening database" << db.lastError().text();
        return -1;
    }

    qDebug() << "Opened database";

    // Создаём модель и заполняем данными
    DriverListModel model;
    QVector<Driver> drivers =  DriverController::getAllByName();
    model.setDrivers(drivers);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("driverModel", &model);
    engine.load(QUrl(QStringLiteral("hello/src/qml/main.qml")));

    return app.exec();
}

