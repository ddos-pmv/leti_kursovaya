#include "DriverController.h"

void DriverController::validateDriver(const Driver &driver) {
    if (driver.name().isEmpty()) {
            throw ValidationException("Driver's name cannot be empty.");
        }
    if (driver.name().length() > 50) {
        throw ValidationException("Driver's name exceeds the maximum length of 50 characters.");
    }

    // Проверка возраста
    if (driver.age() <= 0 || driver.age() > 100) {
        throw ValidationException("Driver's age must be between 1 and 100.");
    }

    // Проверка команды
    if (driver.team().isEmpty()) {
        throw ValidationException("Driver's team cannot be empty.");
    }
    if (driver.team().length() > 100) {
        throw ValidationException("Driver's team name exceeds the maximum length of 100 characters.");
    }
}

QVector<Driver> DriverController::all(const QString &by, bool desc) {
    QSqlDatabase db = QSqlDatabase::database(qgetenv("MAIN_CONNECTION"));
    if (!db.isOpen()) throw DatabaseException("Error opening database: " + db.lastError().text());

    QSqlQuery query(db);
    const QStringList validColumns = {"id", "name", "age", "team", "points"};
    if (!validColumns.contains(by)) throw ValidationException("Invalid column name for sorting: " + by);

    QString sortOrder = desc ? "DESC" : "ASC";

    QString queryString;
    if(sortOrder!= "team" && sortOrder != "points") {
        queryString = QString("SELECT id, name, age, team_id FROM Drivers ORDER BY %1 %2")
                              .arg(by)
                              .arg(sortOrder);
    }
    else {
        queryString = QString("SELECT id, name, age, team_id FROM Drivers");
    }

    if (!query.prepare(queryString)) throw DatabaseException(query.lastError().text());
    if (!query.exec()) throw DatabaseException(query.lastError().text());

    QVector<Driver> drivers;

    while (query.next()) {
        int team_id = query.value("team_id").toInt();
        int driver_id = query.value("id").toInt();


        QSqlQuery pintsQuery(db);

        QString queryPointsString =  QString("SELECT SUM(points) FROM race_participation WHERE driver_id = %1").arg(driver_id);
        if (!pintsQuery.prepare(queryPointsString)) throw DatabaseException(pintsQuery.lastError().text());
        if (!pintsQuery.exec()) throw DatabaseException(pintsQuery.lastError().text());
        if (!pintsQuery.next()) throw ValidationException(pintsQuery.lastError().text());

        int pointsSum = pintsQuery.value(0).toInt();


        QSqlQuery teamQuery(db);
        QString queryTeamString = QString("SELECT name FROM teams WHERE id = %1").arg(team_id);
        if (!teamQuery.prepare(queryTeamString)) throw DatabaseException(teamQuery.lastError().text());
        if (!teamQuery.exec()) throw DatabaseException(teamQuery.lastError().text());
        if (!teamQuery.next()) throw ValidationException(teamQuery.lastError().text());

        QString teamName = teamQuery.value(0).toString();

        drivers.append(Driver(
            driver_id,
            query.value("name").toString(),
            query.value("age").toInt(),
            teamName,
            pointsSum

        ));
    }

    return drivers;
}

void DriverController::add(const QString& name, const int age, const int team_id) {
    QSqlDatabase db = QSqlDatabase::database(qgetenv("MAIN_CONNECTION"));
    if (!db.isOpen()) {
        throw DatabaseException("Error opening database: " + db.lastError().text());
    }

    QSqlQuery query(db);

    // Параметризованный запрос
    if (!query.prepare("INSERT INTO drivers (name, age, team_id) VALUES (:name, :age, :team_id)")) {
        throw DatabaseException(query.lastError().text());
    }

    // Привязка значений к параметрам
    query.bindValue(":name", name);
    query.bindValue(":age", age);
    query.bindValue(":team_id", team_id);

    // Выполнение запроса
    if (!query.exec()) {
        throw DatabaseException(query.lastError().text());
    }
}


void DriverController::update(int id, const QString& name, const int age, const int team_id) {
    QSqlDatabase db = QSqlDatabase::database(qgetenv("MAIN_CONNECTION"));
    if (!db.isOpen()) {
        throw DatabaseException("Error opening database: " + db.lastError().text());
    }

    QSqlQuery query(db);

    // Проверяем существование записи с указанным id
    if (!query.prepare("SELECT id FROM drivers WHERE id = :id")) {
        throw DatabaseException(query.lastError().text());
    }
    query.bindValue(":id", id);

    if (!query.exec()) {
        throw DatabaseException(query.lastError().text());
    }
    if (!query.next()) {
        throw ValidationException("Driver with the specified ID does not exist.");
    }

    // Параметризованный запрос для обновления данных
    if (!query.prepare("UPDATE drivers SET name = :name, age = :age, team_id = :team_id WHERE id = :id")) {
        throw DatabaseException(query.lastError().text());
    }

    query.bindValue(":name", name);
    query.bindValue(":age", age);
    query.bindValue(":team_id", team_id);
    query.bindValue(":id", id);

    // Выполнение запроса
    if (!query.exec()) {
        throw DatabaseException(query.lastError().text());
    }

    qDebug() << "Driver updated successfully.";
}

