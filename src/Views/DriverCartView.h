//
// Created by Сергей Перлин on 10.10.2024.
//

#ifndef DRIVERCARTVIEW_H
#define DRIVERCARTVIEW_H

#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>
#include "../Entities/Driver.h"
#include "../Controllers/DriverController.h"


class DriverCart : public QWidget {
    Q_OBJECT

public:
    DriverCart( QWidget *parent = nullptr) : QWidget(parent) {
        QHBoxLayout *mainLayout = new QHBoxLayout(this);

        QVBoxLayout *infoLayout = new QVBoxLayout();

        photoLabel = new QLabel(this);
        nameLabel = new QLabel(this);
        ageLabel = new QLabel(this);
        teamLabel = new QLabel(this);
        pointsLabel = new QLabel(this);

        infoLayout->addWidget(nameLabel);
        infoLayout->addWidget(ageLabel);
        infoLayout->addWidget(teamLabel);
        infoLayout->addWidget(pointsLabel);

        mainLayout->addWidget(photoLabel);
        mainLayout->addLayout(infoLayout);

        setLayout(mainLayout);
    }


    void updateCartInfo(Driver driver) {
        photoLabel->setPixmap(QString("/Users/sergejperlin/CLionProjects/OOPQt/src/public/carts/max-verstappen-profile-pic.jpeg"));
        nameLabel->setText(driver.getName());
        ageLabel->setText(QString::number(driver.getAge()));
        teamLabel->setText(driver.getTeam());
        pointsLabel->setText(QString::number(driver.getPoints()));
    }

private:
    QLabel *photoLabel;
    QLabel *nameLabel;
    QLabel *ageLabel;
    QLabel *teamLabel;
    QLabel *pointsLabel;
};


#endif //DRIVERCARTVIEW_H
