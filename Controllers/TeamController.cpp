#include "TeamController.h"

void TeamController::validateTeamName(const QString &teamName) {
    if(teamName.isEmpty()) throw ValidationException("Wrong team name");
}

void TeamController::add(const QString &teamName) {
    validateTeamName(teamName);
    QSqlDatabase db = QSqlDatabase::database(qgetenv("MAIN_CONNECTION"));
    if (!db.isOpen()) throw DatabaseException("Error opening database: " + db.lastError().text());

    QString queryString = QString("INSERT INTO teams (name) VALUES (%1)")
    .arg(teamName);

    QSqlQuery query(db);
    if (!query.prepare(queryString)) throw DatabaseException(query.lastError().text());
    if (!query.exec()) throw DatabaseException(query.lastError().text());
}

QVector<Team> TeamController::all() {
    QSqlDatabase db = QSqlDatabase::database(qgetenv("MAIN_CONNECTION"));
    if (!db.isOpen()) throw DatabaseException("Error opening database: " + db.lastError().text());

    QSqlQuery query(db);
    QString queryString = QString("SELECT id, name FROM teams");

    if (!query.prepare(queryString)) throw DatabaseException(query.lastError().text());
    if (!query.exec()) throw DatabaseException(query.lastError().text());

    QVector<Team> teams;

    while (query.next()) {
        teams.append(Team(
            query.value("id").toInt(),
        query.value("name").toString()
        ));
    }

    return teams;
}

QString TeamController::get(const int id) {
    QSqlDatabase db = QSqlDatabase::database(qgetenv("MAIN_CONNECTION"));
    if (!db.isOpen()) throw DatabaseException("Error opening database: " + db.lastError().text());

    QSqlQuery query(db);

    QString queryString = QString("SELECT name FROM teams WHERE id = %1").arg(id);
    if (!query.prepare(queryString)) throw DatabaseException(query.lastError().text());
    if (!query.exec()) throw DatabaseException(query.lastError().text());
    if (!query.next()) throw ValidationException(query.lastError().text());

    return query.value(0).toString();
}

int TeamController::get(const QString& teamName) {
    QSqlDatabase db = QSqlDatabase::database(qgetenv("MAIN_CONNECTION"));
    if (!db.isOpen()) throw DatabaseException("Error opening database: " + db.lastError().text());

    QSqlQuery query(db);

    if (!query.prepare("SELECT id FROM teams WHERE name = :name")) {
        throw DatabaseException("Team controller:" + query.lastError().text());
    }
    query.bindValue(":name", teamName);
    if (!query.exec()) throw DatabaseException("Team controller:" + query.lastError().text());
    if (!query.next()) throw ValidationException("Team controller:" + query.lastError().text());

    return query.value(0).toInt();
}

void TeamController::update(int id, const QString &newName) {
    QSqlDatabase db = QSqlDatabase::database(qgetenv("MAIN_CONNECTION"));
    if (!db.isOpen()) {
        throw DatabaseException("Error opening database: " + db.lastError().text());
    }

    QSqlQuery query(db);

    if (!query.prepare("SELECT id FROM teams WHERE id = :id"))
        throw DatabaseException(query.lastError().text());
    query.bindValue(":id", id);

    if (!query.exec())
        throw DatabaseException(query.lastError().text());
    if (!query.next())
        throw ValidationException("No such team with id: " + QString::number(id));

    if (!query.prepare("UPDATE drivers SET name = :name WHERE id = :id"))
        throw DatabaseException(query.lastError().text());
    query.bindValue(":name", newName);
    query.bindValue(":id", id);


    if (!query.exec())
        throw DatabaseException(query.lastError().text());

    qDebug() << "Team updated successfully";
}
