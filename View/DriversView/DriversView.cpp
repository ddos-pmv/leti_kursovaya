#include "DriversView.h"

DriversView::DriversView(QWidget* parent) : QStackedWidget(parent) {
    listViewWrapper = new QWidget(this);
    listViewWrapper->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    listViewWrapper->setStyleSheet(QString("background-color: transparent; height:%1;").arg(QString::number(MainTheme::RowHeight)));

    auto* mainLayout = new QVBoxLayout(listViewWrapper);
    mainLayout->setSpacing(MainTheme::RowMargin);
    mainLayout->setContentsMargins(0,0,0,0);

    QPushButton* addDriverButton = new QPushButton("Add Driver", listViewWrapper);
    driversListView = new QListView(this);
    driversModel = new DriversModel(this);
    setStyleSheetForListView(driversListView);


    driversListView->setModel(driversModel);
    driversListView->setMouseTracking(true);
    driversListView->setItemDelegate(new DriversDelegate(this));
    driversListView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    driversListView->setSpacing(MainTheme::RowMargin);

    mainLayout->addWidget(addDriverButton);
    mainLayout->addWidget(driversListView);

    listViewWrapper->setLayout(mainLayout);

    QVector<QSharedPointer<Driver>> drivers = DriverController::all();

    for(auto& driver : drivers) {
        driversModel->addDriver(driver);
    }
    driversCard = new DriversCard(this);


    addWidget(listViewWrapper);
    addWidget(driversCard);
    setCurrentIndex(0);

    connect(driversListView, &QListView::clicked, this, [&](const QModelIndex& index) {
        int selectedDriverId =  driversModel->data(index, DriversModel::IdRole).toInt();
        driversCard->setDriver(
            QSharedPointer<Driver>(
                DriverController::getById(selectedDriverId)
                ));

        setCurrentIndex(1);

    });

    connect(driversCard, &DriversCard::closeCart, this, [this]() {
        setCurrentIndex(0);
    });

    connect(driversCard, &DriversCard::driverUpdated, this, [&](QSharedPointer<Driver> driver) {
            int row = driversModel->findDriverRow(driver->id()); // Предполагаем, что метод findDriverRow возвращает индекс гонщика по ID
            if (row != -1) driversModel->updateDriver(row, driver);
    });

    connect(driversCard, &DriversCard::driverDeleted, this, [&](int deletedDriverId) {
            int row = driversModel->findDriverRow(deletedDriverId);
            if(row != -1) driversModel->removeDriver(row);
    });
}


void DriversView::setStyleSheetForListView(QListView* listView) {
    listView->setStyleSheet(QString(R"(
        QListView {
            background-color: transparent;
            border: none;
        }
        QListView::item {
            height: %1px;
            background-color: %2;
            color: %3;
        }
        QListView::item:hover {
            background-color: %4;
            color: %5;
        }
        QListView::item:selected {
            background-color: %6;
            color: %7;
        }
    )").arg(
        QString::number(MainTheme::RowHeight),
        MainTheme::SidebarHoverBackgroundColor.name(),
        MainTheme::SidebarHoverTextColor.name(),
        MainTheme::SidebarSelectedBackgroundColor.name(),
        MainTheme::SidebarSelectedTextColor.name(),
        MainTheme::SidebarSelectedBackgroundColor.name(),
        MainTheme::SidebarSelectedTextColor.name()
        ));
}
