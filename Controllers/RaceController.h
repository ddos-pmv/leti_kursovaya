#ifndef RACECONTROLLER_H
#define RACECONTROLLER_H

#include <QString>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSharedPointer>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

#include "../Exceptions/CustomExceptions.h"
#include "../UpdateManager.h"
#include "../Entities/Race.h"

class RaceController {
public:
    static void validateName(const QString& teamName);

    static QSqlDatabase getDatabase();

    // static void validate(const Race& team);

    static int add(const QString &raceName, const QDateTime &raceTime);
    static QVector<QSharedPointer<Race>> all();
    static QSharedPointer<Race> get(int id);
    static int get(const QString& teamName);
    static void update(int id, const QString &newName, const QDateTime &newTime);
    static void remove(int teamId);
    static int countDrivers(int teamId);


    // static void getDrivers(uint teamId);

private:
    static QSqlQuery prepareAndExecQuery(const QString &queryStr, const QVariantMap &bindValues);
};



#endif //RACECONTROLLER_H
