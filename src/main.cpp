#include <QSqlDatabase>
#include <QApplication>
#include <QDebug>
#include "Models/DriverModel.h"
#include "MainWindow.h"
#include "DatabaseException.h"
#include <QPixmap>
#include <QScreen>

int main(int argc, char *argv[]) {
    qputenv("DB_CONNECTION_STRING", "my");

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "my");
    db.setDatabaseName("racing.db");

    try {
        if (!db.open()) {
            throw DatabaseException("Error opening database: " + db.lastError().text().toStdString());
        }

        qDebug() << "Opened database";

        QApplication app(argc, argv);

        MainWindow window;

        QScreen *screen = QApplication::primaryScreen();
        QRect rect = screen->geometry();
        int x = (rect.width() - window.width()) / 2;
        int y = (rect.height() - window.height()) / 2;
        window.move(x, y);

        window.show();

        return app.exec();
    } catch (const DatabaseException& e) {
        qDebug() << "DatabaseException caught:" << e.what();
        return -1;
    }
}