#ifndef DRIVERSLISTVIEW_H
#define DRIVERSLISTVIEW_H

#include <QVBoxLayout>
#include <QWidget>
#include <QStackedWidget>
#include "CustomTableWidget.h"
#include "../Controllers/DriverController.h"
#include "../Entities/Driver.h"
#include "./Modals/DriverModal.h"
#include <QVector>
#include <QAbstractItemView>
#include <QHeaderView>

#include "DriverCartView.h"


class DriversList : public QStackedWidget {
    Q_OBJECT

public:
    explicit DriversList(QWidget *parent = nullptr) : QStackedWidget(parent) {
        QVBoxLayout *layout = new QVBoxLayout();

        QPushButton *addDriverButton = new QPushButton("+", this);
        layout->addWidget(addDriverButton);

        table = new CustomTableWidget();
        table->setColumnCount(5);
        QStringList headers = {"№", "NAME", "AGE", "TEAM", "POINTS"};
        table->setHorizontalHeaderLabels(headers);
        table->setEditTriggers(QAbstractItemView::NoEditTriggers);
        table->setSelectionMode(QAbstractItemView::NoSelection);

        table->setColumnWidth(0, 30);
        table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
        table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
        table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
        table->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
        table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);

        table->verticalHeader()->hide();
        table->horizontalHeader()->hide();
        table->setShowGrid(false);


        layout->addWidget(table);
        QWidget *container = new QWidget();
        container->setLayout(layout);
        this->addWidget(container);


        populateDriversTable();
        table->initializeBackgroundColors();

        driverCart = new DriverCart(this);
        addWidget(driverCart);

        setCurrentWidget(table);

        connect(addDriverButton, &QPushButton::clicked, this, &DriversList::showAddDriverModal);
        connect(table, &QTableWidget::cellDoubleClicked, this, &DriversList::onDriverDoubleClicked);
    }

private:
    QStackedWidget *stackedWidget;
    DriverCart *driverCart;
    CustomTableWidget *table;

    void populateDriversTable() {
        QVector<Driver> drivers = DriverController::getAllByName();
        table->setRowCount(drivers.size());

        for (int i = 0; i < drivers.size(); i++) {
            const Driver &driver = drivers.at(i);
            table->setItem(i, 0, new QTableWidgetItem(QString::number(driver.getId())));
            table->setItem(i, 1, new QTableWidgetItem(driver.getName()));
            table->setItem(i, 2, new QTableWidgetItem(QString::number(driver.getAge())));
            table->setItem(i, 3, new QTableWidgetItem(driver.getTeam()));
            table->setItem(i, 4, new QTableWidgetItem(QString::number(driver.getPoints())));
        }
    }

public slots:
    void onDriverMenuDoubleClicked(QListWidgetItem *item){
        if (item->text() == "Drivers")
            this->setCurrentWidget(table);
    }
private slots:
    void onDriverDoubleClicked(int row, int column){
        Q_UNUSED(column);
        QString selectedName  = table->item(row, 1)->text();
        QString selectedTeam = table->item(row, 3)->text();

        qDebug() << selectedName << " " << selectedTeam << '\n';

        Driver selectedDriver = DriverController::getByNameAndTeam(selectedName, selectedTeam);

        driverCart->updateCartInfo(selectedDriver);

        this->setCurrentWidget(driverCart);
    }
    void showAddDriverModal() {
        DriverModal *modal = new DriverModal(this);
        modal->exec();
    }
};

#endif // DRIVERSLISTVIEW_H