#include "RaceController.h"


void RaceController::validateName(const QString& raceName) {
    if (raceName.isEmpty()) {
        throw ValidationException("Race name cannot be empty.");
    }
}

QSqlDatabase RaceController::getDatabase() {
    QSqlDatabase db = QSqlDatabase::database(qgetenv("MAIN_CONNECTION"));
    if (!db.isOpen()) {
        throw DatabaseException("Error opening database: " + db.lastError().text());
    }
    return db;
}


int RaceController::add(const QString& raceName, const QDateTime& raceTime) {
    validateName(raceName);
    QSqlQuery query = prepareAndExecQuery("INSERT INTO races (name, date) VALUES (:name, :time)", {{":name", raceName}, {":time", raceTime}});

    return query.lastInsertId().toInt();
}

QVector<QSharedPointer<Race>> RaceController::all() {
    QSqlQuery query = prepareAndExecQuery("SELECT id, name, date FROM races", {});

    QVector<QSharedPointer<Race>> races;
    while (query.next()) {
        races.append(QSharedPointer<Race>::create(
            query.value("id").toInt(),
            query.value("name").toString(),
            query.value("date").toDateTime()
        ));
    }

    return races;
}

QSharedPointer<Race> RaceController::get(int id) {
    QSqlQuery query =  prepareAndExecQuery("SELECT id, name, date FROM races WHERE id = :id", {
        {":id", id}
    });

    if (query.next()) {
        return QSharedPointer<Race>::create(
            query.value("id").toInt(),
            query.value("name").toString(),
            query.value("date").toDateTime()
        );
    }

    return nullptr;
}

int RaceController::get(const QString& raceName) {
    QSqlQuery query = prepareAndExecQuery("SELECT id FROM races WHERE name = :name", {
        {":name", raceName}
    });

    if (query.next()) {
        return query.value("id").toInt();
    }

    return -1;
}

void RaceController::update(int id, const QString& newName, const QDateTime& newTime) {
    validateName(newName);

    QSqlQuery query = prepareAndExecQuery("UPDATE races SET name = :name, date = :time WHERE id = :id", {
        {":name", newName},
        {":time", newTime},
        {":id", id}
    });
}

void RaceController::remove(int raceId) {
    QSqlQuery query = prepareAndExecQuery("DELETE FROM races WHERE id = :id", {{":id", raceId}});
}

int RaceController::countDrivers(int raceId) {
    QSqlQuery query = prepareAndExecQuery("SELECT COUNT(*) FROM race_participation WHERE race_id = :race_id",
        {{":race_id", raceId}});

    if (query.next()) {
        return query.value(0).toInt();
    }

    return 0;
}


QSqlQuery RaceController::prepareAndExecQuery(const QString &queryStr, const QVariantMap &bindValues) {
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