#ifndef DATABASEEXCEPTION_H
#define DATABASEEXCEPTION_H

#include <exception>
#include <string>

class DatabaseException : public std::exception {
public:
    explicit DatabaseException(const std::string& message) : msg_(message) {}

    virtual const char* what() const noexcept override {
        return msg_.c_str();
    }

private:
    std::string msg_;
};

#endif // DATABASEEXCEPTION_H
