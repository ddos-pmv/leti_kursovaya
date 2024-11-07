// main.cpp
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "DriverListModel.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    // Создаём модель и заполняем данными
    DriverListModel model;
    QVector<Driver> drivers = {
        Driver("Max Verstappen", 24, "Red Bull Racing", 332),
        Driver("Lewis Hamilton", 36, "Mercedes", 347),
        Driver("asdfdsf", 3432, "adfadf", 0)
        // Добавьте другие элементы
    };
    model.setDrivers(drivers);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("driverModel", &model);
    engine.load(QUrl(QStringLiteral("hello/src/qml/main.qml")));

    return app.exec();
}
