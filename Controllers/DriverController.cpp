#include "DriverController.h"

#include "../UpdateManager.h"

void DriverController::validateDriver(const Driver &driver) {
    if (driver.name().isEmpty()) {
        throw ValidationException("Driver's name cannot be empty.");
    }
    if (driver.name().length() > 50) {
        throw ValidationException("Driver's name exceeds the maximum length of 50 characters.");
    }

    // Проверка, что имя не состоит только из цифр
    QRegularExpression regex("^[0-9]+$");
    if (regex.match(driver.name()).hasMatch()) {
        throw ValidationException("Driver's name cannot consist only of numbers.");
    }

    // Проверка возраста
    if (driver.age() <= 0 || driver.age() > 100) {
        throw ValidationException("Driver's age must be between 1 and 100.");
    }

    // Проверка команды
    if (driver.team().isEmpty()) {
        throw ValidationException("DriversController: Driver's team cannot be empty.");
    }
    if (driver.team().length() > 100) {
        throw ValidationException("Driver's team name exceeds the maximum length of 100 characters.");
    }
}


QVector<QSharedPointer<Driver>> DriverController::all(const QString& by, bool desc) {
    QSqlDatabase db = QSqlDatabase::database(qgetenv("MAIN_CONNECTION"));
    if (!db.isOpen()) throw DatabaseException("Error opening database: " + db.lastError().text());

    const QStringList validColumns = {"id", "name", "age", "team_name", "total_points"};
    if (!validColumns.contains(by)) throw ValidationException("Invalid column name for sorting: " + by);

    QString sortOrder = desc ? "DESC" : "ASC";

    QString queryString = QString(
        "SELECT d.id, d.name, d.age, t.name AS team_name, "
        "COALESCE(SUM(rp.points), 0) AS total_points "
        "FROM drivers d "
        "LEFT JOIN teams t ON d.team_id = t.id "
        "LEFT JOIN race_participation rp ON d.id = rp.driver_id "
        "GROUP BY d.id, d.name, d.age, t.name "
    );

    QSqlQuery query(db);
    if (!query.prepare(queryString)) throw DatabaseException("DriverController:" + query.lastError().text());
    if (!query.exec()) throw DatabaseException("DriverController: "+ query.lastError().text());

    QVector<QSharedPointer<Driver>> drivers;

    while (query.next()) {
        drivers.append(QSharedPointer<Driver>( new Driver(
            query.value("id").toInt(),
            query.value("name").toString(),
            query.value("age").toInt(),
            query.value("team_name").toString(),
            query.value("total_points").toInt()
        )));
    }

    return drivers;
}


int DriverController::add(const QString& name, const int age, const int team_id) {
    QSqlQuery query = prepareAndExecQuery(
        "INSERT INTO drivers (name, age, team_id) "
        "VALUES (:name, :age, :team_id)",
        {{":name", name},
            {":age", age},
            {":team_id", team_id}});

    bool ok;
    int driverId = query.lastInsertId().toInt(&ok);
    if (!ok) {
        throw DatabaseException("DriversController: Unable to retrieve the ID of the added driver.");
    }


    UpdateManager::instance()->driversInfoUpdated();
    return driverId;
}



void DriverController::update(int id, const QString& name, const int age, const int team_id) {
    if (name.isEmpty()) {
        throw ValidationException("Driver name cannot be empty.");
    }
    if (age <= 0) {
        throw ValidationException("Driver age must be positive.");
    }
    if (team_id <= 0) {
        throw ValidationException("Team ID must be positive.");
    }

    QSqlQuery query = prepareAndExecQuery("UPDATE drivers SET name = :name, age = :age, team_id = :team_id WHERE id = :id", {
        {":name", name},
        {":age", age},
        {":team_id", team_id},
        {":id", id}});

    if (query.numRowsAffected() == 0) {
        throw ValidationException("No driver found with the specified ID: " + QString::number(id));
    }

    UpdateManager::instance()->driversInfoUpdated();
    qDebug() << "Driver with ID" << id << "successfully updated.";
}

QSharedPointer<Driver> DriverController::getById(int id) {
    QSqlQuery query = prepareAndExecQuery("SELECT d.id, d.name, d.age, t.name AS team_name, "
        "COALESCE(SUM(rp.points), 0) AS total_points "
        "FROM drivers d "
        "LEFT JOIN teams t ON d.team_id = t.id "
        "LEFT JOIN race_participation rp ON d.id = rp.driver_id "
        "WHERE d.id = :id "
        "GROUP BY d.id, d.name, d.age, t.name", { {":id", id} });

    if (!query.next()) {
        throw ValidationException("DriversController: No driver found with ID " + QString::number(id));
    }

    int driverId = query.value("id").toInt();
    QString name = query.value("name").toString();
    int age = query.value("age").toInt();
    QString teamName = query.value("team_name").toString();
    int totalPoints = query.value("total_points").toInt();

    return QSharedPointer<Driver>(new Driver(driverId, name, age, teamName, totalPoints));
}

void DriverController::remove(int id) {
    QSqlQuery query = prepareAndExecQuery("DELETE FROM race_participation WHERE driver_id = :id", { {":id", id} });

    query =  prepareAndExecQuery("DELETE FROM drivers WHERE id = :id", { {":id", id} });
    if (query.numRowsAffected() == 0) {
        throw ValidationException("DriversController: No driver found with ID " + QString::number(id));
    }
    UpdateManager::instance()->driversInfoUpdated();
    qDebug() << "Driver with ID" << id << "and associated participation records successfully deleted.";
}


QSqlQuery DriverController::prepareAndExecQuery(const QString& queryStr, const QVariantMap& bindValues = {}) {
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
QSqlDatabase DriverController::getDatabase() {
    QSqlDatabase db = QSqlDatabase::database(qgetenv("MAIN_CONNECTION"));
    if (!db.isOpen()) {
        throw DatabaseException("Error opening database: " + db.lastError().text());
    }
    return db;
}
