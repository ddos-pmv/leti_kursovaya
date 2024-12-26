#include "DriverController.h"

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
    QSqlDatabase db = QSqlDatabase::database(qgetenv("MAIN_CONNECTION"));
    if (!db.isOpen()) {
        throw DatabaseException("DriversController: " + db.lastError().text());
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
        throw DatabaseException("DriversController: " + query.lastError().text());
    }

    // Получение ID последней вставленной записи
    bool ok;
    int driverId = query.lastInsertId().toInt(&ok);

    if (!ok) {
        throw DatabaseException("DriversController: Unable to retrieve the ID of the added driver.");
    }

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

    QSqlDatabase db = QSqlDatabase::database(qgetenv("MAIN_CONNECTION"));
    if (!db.isOpen()) {
        throw DatabaseException("DriversController: Failed to open database: " + db.lastError().text());
    }

    QSqlQuery query(db);
    if (!query.prepare("UPDATE drivers SET name = :name, age = :age, team_id = :team_id WHERE id = :id")) {
        throw DatabaseException("DriversController: Failed to prepare update query: " + query.lastError().text());
    }

    query.bindValue(":name", name);
    query.bindValue(":age", age);
    query.bindValue(":team_id", team_id);
    query.bindValue(":id", id);

    if (!query.exec()) {
        throw DatabaseException("DriversController: Failed to execute update query: " + query.lastError().text());
    }

    if (query.numRowsAffected() == 0) {
        throw ValidationException("No driver found with the specified ID: " + QString::number(id));
    }

    qDebug() << "Driver with ID" << id << "successfully updated.";
}

QSharedPointer<Driver> DriverController::getById(int id) {
    QSqlDatabase db = QSqlDatabase::database(qgetenv("MAIN_CONNECTION"));
    if (!db.isOpen()) {
        throw DatabaseException("DriversController: Failed to open database: " + db.lastError().text());
    }

    QSqlQuery query(db);
    QString queryString = QString(
        "SELECT d.id, d.name, d.age, t.name AS team_name, "
        "COALESCE(SUM(rp.points), 0) AS total_points "
        "FROM drivers d "
        "LEFT JOIN teams t ON d.team_id = t.id "
        "LEFT JOIN race_participation rp ON d.id = rp.driver_id "
        "WHERE d.id = :id "
        "GROUP BY d.id, d.name, d.age, t.name"
    );


    if (!query.prepare(queryString)) {
        throw DatabaseException("DriversController: Failed to prepare query: " + query.lastError().text());
    }

    query.bindValue(":id", id);

    if (!query.exec()) {
        throw DatabaseException("DriversController: Failed to execute query: " + query.lastError().text());
    }

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
    QSqlDatabase db = QSqlDatabase::database(qgetenv("MAIN_CONNECTION"));
    if (!db.isOpen()) {
        throw DatabaseException("DriversController: Failed to open database: " + db.lastError().text());
    }

    QSqlQuery query(db);

    // Удаление записей из race_participation
    if (!query.prepare("DELETE FROM race_participation WHERE driver_id = :id")) {
        throw DatabaseException("DriversController: Failed to prepare race_participation deletion query: " + query.lastError().text());
    }
    query.bindValue(":id", id);

    if (!query.exec()) {
        throw DatabaseException("DriversController: Failed to execute race_participation deletion query: " + query.lastError().text());
    }

    // Удаление гонщика из drivers
    if (!query.prepare("DELETE FROM drivers WHERE id = :id")) {
        throw DatabaseException("DriversController: Failed to prepare drivers deletion query: " + query.lastError().text());
    }
    query.bindValue(":id", id);

    if (!query.exec()) {
        throw DatabaseException("DriversController: Failed to execute drivers deletion query: " + query.lastError().text());
    }

    if (query.numRowsAffected() == 0) {
        throw ValidationException("DriversController: No driver found with ID " + QString::number(id));
    }

    qDebug() << "Driver with ID" << id << "and associated participation records successfully deleted.";
}


