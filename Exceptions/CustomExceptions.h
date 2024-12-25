#ifndef CUSTOMEXCEPTIONS_H
#define CUSTOMEXCEPTIONS_H

#include <exception>
#include <QString>
#include <string>

class AppException : public std::exception {
protected:
    QString message;
    std::string cachedMessage; // Буфер для хранения строки в формате std::string

    void updateCachedMessage(const QString& prefix) {
        cachedMessage = (prefix + message).toStdString();
    }

public:
    explicit AppException(const QString& msg) : message(msg) {
        updateCachedMessage("AppException: ");
    }

    const char* what() const noexcept override {
        return cachedMessage.c_str();
    }

    QString getMessage() const {
        return message;
    }
};

class DataException : public AppException {
public:
    explicit DataException(const QString& msg) : AppException(msg) {
        updateCachedMessage("DataException: ");
    }
};

class DatabaseException : public AppException {
public:
    explicit DatabaseException(const QString& msg) : AppException(msg) {
        updateCachedMessage("DatabaseException: ");
    }
};

class ValidationException : public AppException {
public:
    explicit ValidationException(const QString& msg) : AppException(msg) {
        updateCachedMessage("ValidationException: ");
    }
};

class LogicException : public AppException {
public:
    explicit LogicException(const QString& msg) : AppException(msg) {
        updateCachedMessage("LogicException: ");
    }
};

#endif // CUSTOMEXCEPTIONS_H
