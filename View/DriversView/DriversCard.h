//
// Created by Сергей Перлин on 25.12.2024.
//

#ifndef DRIVERSCARD_H
#define DRIVERSCARD_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QSharedPointer>

#include "../../Controllers/DriverController.h"
#include "../../Controllers/TeamController.h"
#include "../../Entities/Driver.h"

class DriversCard : public QWidget {
    Q_OBJECT

public:
    explicit DriversCard(QWidget* parent = nullptr) : QWidget(parent) {
        auto* mainLayout = new QVBoxLayout(this);

        // Поля для редактирования данных
        nameEdit = new QLineEdit(this);
        ageEdit = new QLineEdit(this);
        teamEdit = new QLineEdit(this);

        // Метки
        nameLabel = new QLabel("Name:", this);
        ageLabel = new QLabel("Age:", this);
        teamLabel = new QLabel("Team:", this);

        auto* nameLayout = new QHBoxLayout();
        nameLayout->addWidget(nameLabel);
        nameLayout->addWidget(nameEdit);

        auto* ageLayout = new QHBoxLayout();
        ageLayout->addWidget(ageLabel);
        ageLayout->addWidget(ageEdit);

        auto* teamLayout = new QHBoxLayout();
        teamLayout->addWidget(teamLabel);
        teamLayout->addWidget(teamEdit);

        mainLayout->addLayout(nameLayout);
        mainLayout->addLayout(ageLayout);
        mainLayout->addLayout(teamLayout);

        // Кнопки
        saveButton = new QPushButton("Save", this);
        deleteButton = new QPushButton("Delete", this);
        cancelButton = new QPushButton("Cancel", this);

        auto* buttonLayout = new QHBoxLayout();
        buttonLayout->addWidget(saveButton);
        buttonLayout->addWidget(deleteButton);

        mainLayout->addLayout(buttonLayout);

        // Подключение сигналов
        connect(saveButton, &QPushButton::clicked, this, &DriversCard::saveDriver);
        connect(deleteButton, &QPushButton::clicked, this, &DriversCard::deleteDriver);
        connect(cancelButton, &QPushButton::clicked, this, [&]() {
            emit closeCart();
        });
    }

    void setDriver(QSharedPointer<Driver> driver) {
        currentDriver = driver;
        nameEdit->setText(driver->name());
        ageEdit->setText(QString::number(driver->age()));
        teamEdit->setText(driver->team());
    }

signals:
    void driverUpdated(QSharedPointer<Driver> driver); // Сигнал при сохранении изменений
    void driverDeleted(int driverId);                 // Сигнал при удалении
    void closeCart();

private slots:
    void saveDriver() {
        if (!currentDriver) {
            QMessageBox::warning(this, "Error", "No driver loaded.");
            return;
        }

        try {
            // Обновление данных
            currentDriver->setName(nameEdit->text());
            currentDriver->setAge(ageEdit->text().toInt());
            currentDriver->setTeam(teamEdit->text());

            DriverController::validateDriver(*currentDriver);

            int newTeamId = TeamController::get(teamEdit->text());

            // Сохранение в БД
            DriverController::update(currentDriver->id(),
                                      currentDriver->name(),
                                      currentDriver->age(),
                                      newTeamId); // предполагается, что `team_id` в базе.

            emit driverUpdated(currentDriver);
            QMessageBox::information(this, "Success", "Driver updated successfully.");
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", e.what());
        }
    }

    void deleteDriver() {
        if (!currentDriver) {
            QMessageBox::warning(this, "Error", "No driver loaded.");
            return;
        }

        auto reply = QMessageBox::question(this, "Confirm Delete",
                                           "Are you sure you want to delete this driver?");
        if (reply == QMessageBox::Yes) {
            try {
                DriverController::remove(currentDriver->id());
                emit driverDeleted(currentDriver->id());
                QMessageBox::information(this, "Success", "Driver deleted successfully.");
                currentDriver.reset(); // Сброс текущего гонщика
            } catch (const std::exception& e) {
                QMessageBox::critical(this, "Error", e.what());
            }
        }
    }

private:
    QLineEdit* nameEdit;
    QLineEdit* ageEdit;
    QLineEdit* teamEdit;

    QLabel* nameLabel;
    QLabel* ageLabel;
    QLabel* teamLabel;

    QPushButton* saveButton;
    QPushButton* deleteButton;
    QPushButton* cancelButton;

    QSharedPointer<Driver> currentDriver;
};

#endif //DRIVERSCARD_H
