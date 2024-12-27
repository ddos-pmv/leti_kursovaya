#ifndef TEAMCONTROLLER_H
#define TEAMCONTROLLER_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVector>
#include <QVariant>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <stdexcept>


#include "../Exceptions/CustomExceptions.h"
#include "../Entities/Team.h"
#include "../UpdateManager.h"


class TeamController {
public:
    static void validateTeamName(const QString& teamName);

    static QSqlDatabase getDatabase();

    static void validate(const Team& team);

    static int add(const QString& teamName);
    static QVector<QSharedPointer<Team>> all();
    static QSharedPointer<Team> get(int id);
    static int get(const QString& teamName);
    static void update(int id, const QString& newName);
    static void remove(int teamId);
    static int countDrivers(int teamId);

    static void getDrivers(uint teamId);

private:
    static QSqlQuery prepareAndExecQuery(const QString &queryStr, const QVariantMap &bindValues);
};
#endif //TEAMCONTROLLER_H
