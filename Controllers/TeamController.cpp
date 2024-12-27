#include "TeamController.h"

void TeamController::validateTeamName(const QString &teamName) {
    if (teamName.isEmpty()) {
        throw ValidationException("Team name cannot be empty.");
    }
}

QSqlDatabase TeamController::getDatabase() {
    QSqlDatabase db = QSqlDatabase::database(qgetenv("MAIN_CONNECTION"));
    if (!db.isOpen()) {
        throw DatabaseException("Error opening database: " + db.lastError().text());
    }
    return db;
}

void TeamController::validate(const Team& team) {
    if (team.name().isEmpty()) {
        throw ValidationException("Team name cannot be empty.");
    }
    if (team.driversCol() < 0) {
        throw ValidationException("Number of drivers cannot be less than 0.");
    }
}

int TeamController::add(const QString &teamName) {
    validateTeamName(teamName);
    QSqlQuery query = prepareAndExecQuery("INSERT INTO teams (name) VALUES (:name)", {{":name", teamName}});

    bool ok;
    int teamId = query.lastInsertId().toInt(&ok);

    if (!ok) {
        throw DatabaseException("Unable to retrieve the ID of the added team.");
    }
    UpdateManager::instance()->teamsInfoUpdated();
    return teamId;
}

QVector<QSharedPointer<Team>> TeamController::all() {
    QSqlQuery query;
    query = prepareAndExecQuery("SELECT t.id, t.name, "
            "(SELECT COUNT(*) FROM drivers d WHERE d.team_id = t.id) AS drivers_count, "
            "(SELECT COALESCE(SUM(rp.points), 0) "
            " FROM drivers d "
            " LEFT JOIN race_participation rp ON d.id = rp.driver_id "
            " WHERE d.team_id = t.id) AS total_points "
            "FROM teams t", {});

    QVector<QSharedPointer<Team>> teams;
    while (query.next()) {
        int teamId = query.value("id").toInt();
        QString teamName = query.value("name").toString();
        int driversCount = query.value("drivers_count").toInt();
        int totalPoints = query.value("total_points").toInt();

        teams.append(QSharedPointer<Team>::create(teamId, teamName, driversCount, totalPoints));
    }

    return teams;
}

QSharedPointer<Team> TeamController::get(const int id) {
    QSqlDatabase db = getDatabase();

    QSqlQuery query(db);
    if (!query.prepare(
            "SELECT t.id, t.name, "
            "(SELECT COUNT(*) FROM drivers d WHERE d.team_id = t.id) AS drivers_count, "
            "(SELECT COALESCE(SUM(rp.points), 0) "
            " FROM drivers d "
            " LEFT JOIN race_participation rp ON d.id = rp.driver_id "
            " WHERE d.team_id = t.id) AS total_points "
            "FROM teams t"
            " WHERE id = :id")) {
        throw DatabaseException("Error getting team" + query.lastError().text());
    }

    query.bindValue(":id", id);

    if (!query.exec()) {
        throw DatabaseException("Error executing query: " + query.lastError().text());
    }
    if (!query.next()) {
        throw ValidationException("Team not found with id: " + QString::number(id));
    }

    return QSharedPointer<Team>::create(
        query.value("id").toInt(),
    query.value("name").toString(),
    query.value("drivers_count").toInt(),
    query.value("total_points").toInt());
}

int TeamController::get(const QString &teamName) {
    QSqlDatabase db = getDatabase();

    QSqlQuery query = prepareAndExecQuery("SELECT id FROM teams WHERE name = :name", {{":name", teamName}});
    if (!query.next()) {
        throw ValidationException("Team not found with name: " + teamName);
    }

    return query.value(0).toInt();
}

void TeamController::update(int id, const QString &newName) {
    validateTeamName(newName);
    QSqlQuery query;

    query = prepareAndExecQuery(QString("SELECT id FROM teams WHERE id = :id"), {{":id", id}});

    if (!query.next()) {
        throw ValidationException("No such team with id: " + QString::number(id));
    }

    // Update the team name
    prepareAndExecQuery("UPDATE teams SET name = :name WHERE id = :id", {{":name", newName}, {":id", id}});
    UpdateManager::instance()->teamsInfoUpdated();
}

void TeamController::remove(int teamId) {
    if (countDrivers(teamId) == 0) {
        QString queryStr = "DELETE FROM teams WHERE id = :teamId";
        prepareAndExecQuery(queryStr, { {":teamId", teamId} });
    }
    else {
        throw ValidationException("Cannot delete team with drivers assigned to it.");
    }

}

int TeamController::countDrivers(int teamId) {
    QSqlQuery query =  prepareAndExecQuery("SELECT COUNT(*) FROM drivers WHERE team_id = :teamId",
        {{":teamId", teamId}});
    if (!query.next()) {
        throw ValidationException("Team was not found with id: " + QString::number(teamId));
    }
    return query.value(0).toInt();
}


QSqlQuery TeamController::prepareAndExecQuery(const QString& queryStr, const QVariantMap& bindValues = {}) {
    QSqlDatabase db = getDatabase();
    QSqlQuery query(db);

    if (!query.prepare(queryStr)) {
        throw DatabaseException("Error preparing query: " + query.lastError().text());
    }

    for (auto it = bindValues.constBegin(); it != bindValues.constEnd(); ++it) {
        query.bindValue(it.key(), it.value());
    }

    if (!query.exec()) {
        throw DatabaseException("Error executing query: " + query.lastError().text());
    }

    return query;
}