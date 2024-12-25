#include "TeamController.h"
#include <QVariant>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <stdexcept>

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

void TeamController::add(const QString &teamName) {
    validateTeamName(teamName);
    QSqlDatabase db = getDatabase();

    QSqlQuery query(db);
    if (!query.prepare("INSERT INTO teams (name) VALUES (:name)")) {
        throw DatabaseException("Error preparing query: " + query.lastError().text());
    }
    query.bindValue(":name", teamName);

    if (!query.exec()) {
        throw DatabaseException("Error executing query: " + query.lastError().text());
    }
}

QVector<Team> TeamController::all() {
    QSqlDatabase db = getDatabase();

    QSqlQuery query(db);
    if (!query.prepare("SELECT id, name FROM teams")) {
        throw DatabaseException("Error preparing query: " + query.lastError().text());
    }

    if (!query.exec()) {
        throw DatabaseException("Error executing query: " + query.lastError().text());
    }

    QVector<Team> teams;
    while (query.next()) {
        teams.append(Team(query.value("id").toInt(), query.value("name").toString()));
    }

    return teams;
}

QString TeamController::get(const int id) {
    QSqlDatabase db = getDatabase();

    QSqlQuery query(db);
    if (!query.prepare("SELECT name FROM teams WHERE id = :id")) {
        throw DatabaseException("Error preparing query: " + query.lastError().text());
    }
    query.bindValue(":id", id);

    if (!query.exec()) {
        throw DatabaseException("Error executing query: " + query.lastError().text());
    }
    if (!query.next()) {
        throw ValidationException("Team not found with id: " + QString::number(id));
    }

    return query.value(0).toString();
}

int TeamController::get(const QString &teamName) {
    QSqlDatabase db = getDatabase();

    QSqlQuery query(db);
    if (!query.prepare("SELECT id FROM teams WHERE name = :name")) {
        throw DatabaseException("Error preparing query: " + query.lastError().text());
    }
    query.bindValue(":name", teamName);

    if (!query.exec()) {
        throw DatabaseException("Error executing query: " + query.lastError().text());
    }
    if (!query.next()) {
        throw ValidationException("Team not found with name: " + teamName);
    }

    return query.value(0).toInt();
}

void TeamController::update(int id, const QString &newName) {
    validateTeamName(newName);

    QSqlDatabase db = getDatabase();
    QSqlQuery query(db);

    // Check if the team exists
    if (!query.prepare("SELECT id FROM teams WHERE id = :id")) {
        throw DatabaseException("Error preparing query: " + query.lastError().text());
    }
    query.bindValue(":id", id);

    if (!query.exec()) {
        throw DatabaseException("Error executing query: " + query.lastError().text());
    }
    if (!query.next()) {
        throw ValidationException("No such team with id: " + QString::number(id));
    }

    // Update the team name
    if (!query.prepare("UPDATE teams SET name = :name WHERE id = :id")) {
        throw DatabaseException("Error preparing query: " + query.lastError().text());
    }
    query.bindValue(":name", newName);
    query.bindValue(":id", id);

    if (!query.exec()) {
        throw DatabaseException("Error executing query: " + query.lastError().text());
    }

    qDebug() << "Team updated successfully.";
}
