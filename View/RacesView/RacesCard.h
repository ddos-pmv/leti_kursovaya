#ifndef RACESCARD_H
#define RACESCARD_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QMessageBox>
#include <QSharedPointer>
#include <QInputDialog>

#include "../../Controllers/RaceController.h"
#include "../../Controllers/DriverController.h"
#include "../../Entities/Driver.h"
#include "../../Entities/Race.h"

class RacesCard : public QWidget {
    Q_OBJECT

public:
    explicit RacesCard(QWidget* parent = nullptr) : QWidget(parent) {
        auto* mainLayout = new QVBoxLayout(this);

        nameLabel = new QLabel("Drivers in Race", this);
        cancelBtn = new QPushButton("Back", this);
        addButton = new QPushButton("Add Driver", this);
        removeButton = new QPushButton("Remove Driver", this);
        driversList = new QListWidget(this);

        mainLayout->addWidget(nameLabel);
        mainLayout->addWidget(driversList);
        mainLayout->addWidget(addButton);
        mainLayout->addWidget(removeButton);

        setLayout(mainLayout);

        connect(addButton, &QPushButton::clicked, this, &RacesCard::addDriver);
        connect(cancelBtn, &QPushButton::clicked, this, [&]() {
            emit closeCard();
        });
        connect(removeButton, &QPushButton::clicked, this, &RacesCard::removeDriver);
    }

    void setRace(int raceId) {
        currentRaceId = raceId;
        driversList->clear();
        try {
            QVector<QSharedPointer<Driver>> drivers = DriverController::getDriversByRaceId(raceId);
            for (const auto& driver : drivers) {
                int points = DriverController::getDriverPointsInRace(driver->id(), raceId);
                driversList->addItem(driver->name() + " - " + driver->team() + " - Points: " + QString::number(points));
            }
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", e.what());
        }
    }
signals:
    void closeCard();
private slots:
    void addDriver() {
        bool ok;
        QString driverName = QInputDialog::getText(this, "Add Driver", "Driver name:", QLineEdit::Normal, "", &ok);
        if (!ok || driverName.isEmpty()) return;

        QString teamName = QInputDialog::getText(this, "Add Driver", "Team name:", QLineEdit::Normal, "", &ok);
        if (!ok || teamName.isEmpty()) return;

        int points = QInputDialog::getInt(this, "Add Driver", "Points:", 0, 0, 1000, 1, &ok);
        if (!ok) return;

        try {
            int driverId = DriverController::getDriverByNameAndTeam(driverName, teamName)->id();
            DriverController::addDriverToRace(driverId, currentRaceId, points);
            setRace(currentRaceId); // Refresh the list
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", e.what());
        }
    }

    void removeDriver() {
    QListWidgetItem* item = driversList->currentItem();
    if (!item) {
        QMessageBox::warning(this, "Remove Driver", "Please select a driver to remove.");
        return;
    }

    QStringList parts = item->text().split(" - ");
    if (parts.size() < 2) {
        QMessageBox::warning(this, "Remove Driver", "Invalid driver information.");
        return;
    }

    QString driverName = parts[0];
    QString teamName = parts[1];

    try {
        int driverId = DriverController::getDriverByNameAndTeam(driverName, teamName)->id();
        DriverController::removeDriverFromRace(driverId, currentRaceId);
        setRace(currentRaceId); // Refresh the list
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}

private:
    QLabel* nameLabel;
    QListWidget* driversList;
    QPushButton* addButton;
    QPushButton* removeButton;
    QPushButton* cancelBtn;
    int currentRaceId;
};

#endif // RACESCARD_H