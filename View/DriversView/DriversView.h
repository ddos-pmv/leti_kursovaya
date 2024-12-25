#ifndef DRIVERMAINVIEW_H
#define DRIVERMAINVIEW_H

#include <QStackedWidget>
#include <QWidget>
#include <QListView>

#include "../../Models/DriversModel.h"
#include "DriversDelegate.h"
#include "../../Entities/Driver.h"
#include "../../Controllers/DriverController.h"

class DriversView : public QStackedWidget {
public:
    explicit DriversView(QWidget* parent = nullptr) : QStackedWidget(parent) {
        driversListView = new QListView(this);
        driversModel = new DriversModel(this);

        QVector<QSharedPointer<Driver>> drivers = DriverController::all();

        for(auto& driver : drivers) {
            driversModel->addDriver(driver);
        }

        addWidget(driversListView);
        setCurrentIndex(0);
    }

private:
    QListView* driversListView;
    DriversModel* driversModel;

};

#endif //DRIVERMAINVIEW_H
