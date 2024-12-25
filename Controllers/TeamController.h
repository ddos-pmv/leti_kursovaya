#ifndef TEAMCONTROLLER_H
#define TEAMCONTROLLER_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVector>

#include "TeamController.h"

#include "../Exceptions/CustomExceptions.h"
#include "../Entities/Team.h"


class TeamController {
private:

public:
    static void validateTeamName(const QString& teamName);
    static void add(const QString& teamName);
    static QVector<Team> all();
    static QString get(int id);
    static int get(const QString& teamName);
    static void update(int id, const QString& newName);


};
#endif //TEAMCONTROLLER_H
