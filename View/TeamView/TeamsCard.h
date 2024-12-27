#ifndef TEAMSCARD_H
#define TEAMSCARD_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QListWidget>
#include <QSharedPointer>

#include "../../Controllers/TeamController.h"
#include "../../Entities/Team.h"
#include "../../Controllers/DriverController.h"
#include "../../Entities/Driver.h"

class TeamsCard : public QWidget {
    Q_OBJECT

public:
    explicit TeamsCard(QWidget* parent = nullptr) : QWidget(parent) {
        auto* mainLayout = new QVBoxLayout(this);

        nameLabel = new QLabel("Drivers", this);
        cancelButton = new QPushButton("Go back", this);
        driversList = new QListWidget(this);
        mainLayout->addWidget(cancelButton);
        mainLayout->addWidget(driversList);
        mainLayout->addWidget(nameLabel);

        setLayout(mainLayout);

        connect(cancelButton, &QPushButton::clicked, this, [&]() {
            emit closeCard();
        });
    }

    void setTeam(int teamId) {
        driversList->clear();
        try {
            QVector<QSharedPointer<Driver>> drivers  = DriverController::getDriversByTeamId(teamId);
            for (const auto& driver : drivers) {
                driversList->addItem(driver->name());
            }
        }
        catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", e.what());
            emit closeCard();
        }
    }

signals:
    void teamUpdated(QSharedPointer<Team> team); // Сигнал при сохранении изменений
    void teamDeleted(int teamId);                // Сигнал при удалении
    void closeCard();


private:
    QLabel* nameLabel;
    QListWidget* driversList;

    QPushButton* saveButton;
    QPushButton* deleteButton;
    QPushButton* cancelButton;

    QSharedPointer<Team> currentTeam;
};

#endif // TEAMSCARD_H