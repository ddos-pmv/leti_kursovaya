#include "DriversView.h"

DriversView::DriversView(QWidget* parent) : QStackedWidget(parent) {
    listViewWrapper = new QWidget(this);
    listViewWrapper->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    listViewWrapper->setStyleSheet(QString("QWidget{"
                                           "background-color: transparent; "
                                           "height:%1;"
                                           "}").arg(QString::number(MainTheme::RowHeight)));
    listViewWrapper->setContentsMargins(0,0,0,0);

    auto* mainLayout = new QVBoxLayout(listViewWrapper);
    mainLayout->setSpacing(MainTheme::RowMargin);
    mainLayout->setContentsMargins(0,0,0,0);

    driversListView = new QListView(this);
    driversModel = new DriversModel(this);
    setStyleSheetForListView(driversListView);

    sortProxyModel = new QSortFilterProxyModel(this);
    sortProxyModel->setSortRole(DriversModel::IdRole);
    sortProxyModel->setSourceModel(driversModel);
    driversListView->setModel(sortProxyModel);
    driversListView->setMouseTracking(true);
    driversListView->setItemDelegate(new DriversDelegate(this));
    driversListView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    driversListView->setSpacing(MainTheme::RowMargin);

    controlHeader = createControlHeader(listViewWrapper);
    mainLayout->addWidget(controlHeader);
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

    connect(addDriverButton, &QPushButton::clicked, this, &DriversView::showAddDriverDialog);
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
            setCurrentIndex(0);
    });

    connect(driversCard, &DriversCard::driverDeleted, this, [&](int deletedDriverId) {
            int row = driversModel->findDriverRow(deletedDriverId);
            if(row != -1) driversModel->removeDriver(row);
            setCurrentIndex(0);
    });
}


void DriversView::setStyleSheetForListView(QListView* listView) {
    listView->setContentsMargins(0,0,0,0);
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

void DriversView::showAddDriverDialog() {
    AddDriverDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {
        QString name = dialog.getName();
        int age = dialog.getAge();
        QString team = dialog.getTeam();

        try {
            int teamId = TeamController::get(team);
            DriverController::validateDriver(Driver(name, age, team));
            int id = DriverController::add(name, age, teamId);

            QSharedPointer<Driver> newDriver = DriverController::getById(id);
            driversModel->addDriver(newDriver);
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", e.what());
        }
    }
}

QWidget* DriversView::createControlHeader(QWidget *parent) {
    auto row = new QWidget(parent);
    auto layout = new QHBoxLayout(row);
    layout->setContentsMargins(0,0,0,0);

    row->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    row->setFixedHeight(MainTheme::RowHeight);

    row->setStyleSheet("QPushButton{"
                       "background-color: white;"
                       "color: black;"
                       "}");

    addDriverButton = new QPushButton("+", parent);
    sortByName = new QPushButton("By name", parent);
    sortByAge = new QPushButton("By age", parent);
    sortByTeam = new QPushButton("By team", parent);
    sortByPoints = new QPushButton("By points", parent);

    layout->addWidget(addDriverButton);
    layout->addWidget(sortByName);
    layout->addWidget(sortByAge);
    layout->addWidget(sortByTeam);
    layout->addWidget(sortByPoints);

    row->setLayout(layout);


    connect(sortByName, &QPushButton::clicked, this, [&]() {
        if(sortProxyModel!=nullptr) {
            sortProxyModel->setSortRole(DriversModel::NameRole);
            nameInc = !nameInc;
            auto sortOrder = nameInc ? Qt::AscendingOrder : Qt::DescendingOrder;
            sortProxyModel->sort(0, sortOrder);
        }
    });

    connect(sortByAge, &QPushButton::clicked, this, [&]() {
        if(sortProxyModel!=nullptr) {
            sortProxyModel->setSortRole(DriversModel::AgeRole);
            ageInc = !ageInc;
            auto sortOrder = ageInc ? Qt::AscendingOrder : Qt::DescendingOrder;
            sortProxyModel->sort(0, sortOrder);
        }
    });
    connect(sortByTeam, &QPushButton::clicked, this, [&]() {
        if(sortProxyModel!=nullptr) {
            sortProxyModel->setSortRole(DriversModel::TeamRole);
            teamInc = !teamInc;
            auto sortOrder = teamInc ? Qt::AscendingOrder : Qt::DescendingOrder;
            sortProxyModel->sort(0, sortOrder);
        }
    });

    connect(sortByPoints, &QPushButton::clicked, this, [&]() {
        if(sortProxyModel!=nullptr) {
            sortProxyModel->setSortRole(DriversModel::PointsRole);
            pointsInc = !pointsInc;
            auto sortOrder = pointsInc ? Qt::AscendingOrder : Qt::DescendingOrder;
            sortProxyModel->sort(0, sortOrder);
        }
    });

    return row;
}
