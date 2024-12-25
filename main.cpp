#include <QApplication>
#include <QSettings>
#include <QSqlDatabase>

#include "View/MainWindow.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    QSettings localConfig(":/config.ini", QSettings::Format::IniFormat);
    qputenv("MAIN_CONNECTION", localConfig.value("Database/connectionName").toByteArray());


    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", qgetenv("MAIN_CONNECTION"));
    db.setDatabaseName(localConfig.value("Database/name").toString());
    try {
        if(db.databaseName().isEmpty()) throw DatabaseException("Db name is empty");
        if(!db.open()) throw DatabaseException("Error opening database: " +  db.lastError().text());

        qDebug() << db.connectionName();
    }
    catch(const AppException & e) {
        qWarning() << e.what();
        db.close();
        return EXIT_FAILURE;
    }

    MainWindow w;
    w.show();
    return a.exec();
}
