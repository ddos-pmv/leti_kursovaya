//
// Created by Сергей Перлин on 04.10.2024.
//

#ifndef DB_H
#define DB_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

bool connectToDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    // Настройки подключения к MySQL
    db.setHostName("127.0.0.1");  // Локальный сервер
    db.setPort(3306);             // Порт MySQL
    db.setDatabaseName("racing_db");  // Имя базы данных
    db.setUserName("root");       // Имя пользователя MySQL
    db.setPassword("password");   // Пароль пользователя

    // Подключение
    if (!db.open()) {
        qDebug() << "Ошибка подключения к базе данных:" << db.lastError().text();
        return false;
    }

    qDebug() << "Подключение к базе данных успешно!";
    return true;
}


#endif //DB_H
