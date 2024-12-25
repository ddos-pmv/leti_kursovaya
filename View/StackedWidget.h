//
// Created by Сергей Перлин on 23.12.2024.
//

#ifndef STACKEDWIDGET_H
#define STACKEDWIDGET_H

#include <QStackedWidget>
#include <QList>
#include <QStackedLayout>
#include <QDialog>

#include "List.h"
#include "../Models/DriversModel.h"
#include "../Controllers/DriverController.h"
#include "MainThemeVars.h"
#include "../Entities/Driver.h"
#include "DriversView/DriversView.h"

class StackedWidget : public QStackedWidget {
public:
    explicit StackedWidget(QWidget* parent = nullptr) : QStackedWidget(parent) {
        driverView = new DriversView(this);

        addWidget(driverView);
        setCurrentIndex(0);
        connect(driverView->listView(), &QListView::clicked, this, [this](const QModelIndex& index) {
           qDebug() << "Selected:" << driverView->model()->data(index, DriversModel::NameRole).toString();
        });
    }
private:
    DriversView* driverView;

    void setupDriversContent();
};



#endif //STACKEDWIDGET_H
