#include <QSqlDatabase>
#include <QApplication>
#include <QDebug>
#include "Models/DriverModel.h"
#include "MainWindow.h"
#include <QPixmap>
#include <QScreen>
int main (int argc, char *argv[]) {
    qputenv("DB_CONNECTION_STRING", "my");

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "my");
    db.setDatabaseName("racing.db");

    if(!db.open()) {
        qDebug() << "Error opening database" << db.lastError().text();
        return -1;
    }

    qDebug() << "Opened database";

    QApplication app(argc, argv);

    MainWindow window;

    QScreen *screen = QApplication::primaryScreen();
    QRect rect = screen->geometry();
    int x = (rect.width() - window.width()) / 2;
    int y = (rect.height() - window.height()) / 2;
    window.move(x, y);
    // window.setAttribute(Qt::WA_TranslucentBackground, true);

        // QPalette pal = window.palette(); pal.setBrush(QPalette::Normal, QPalette::Window,
        //     QBrush(QPixmap("./bg.png")));
        // window.setPalette(pal);



    window.show();


    //
    // DriverModel driverModel;
    // QVector<Driver> drivers = DriverModel::getAllSortedByName();
    //
    // for(int i = 0; i < drivers.count(); i++) {
    //     qDebug() << drivers[i].getInfo() << '\n';
    // }


    return app.exec();
}