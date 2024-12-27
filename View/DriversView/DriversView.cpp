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


    // setup model
    sortProxyModel = new QSortFilterProxyModel(this);
    sortProxyModel->setSourceModel(driversModel);
    sortProxyModel->setSortRole(DriversModel::IdRole);
    sortProxyModel->sort(0, Qt::AscendingOrder);

    driversListView->setModel(sortProxyModel);
    driversListView->setMouseTracking(true);
    driversListView->setItemDelegate(new DriversDelegate(this));
    driversListView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    driversListView->setSpacing(MainTheme::RowMargin);

    controlHeader = createControlHeader(listViewWrapper);


    // setup title header
    titleHeader = new QWidget(listViewWrapper);
    titleHeader->setContentsMargins(0,0,0,0);
    titleHeaderLayout = new QHBoxLayout(titleHeader);
    titleHeaderLayout->setSpacing(MainTheme::RowMargin);
    titleHeader->setContentsMargins(0,0,0,0);
    titleHeader->setStyleSheet(QString("QPushButton{background-color: white; color: black;}"));
    titleHeader->setLayout(titleHeaderLayout);
    titleHeader->setContentsMargins(0,0,0,0);


    teamButton = new QPushButton("Team", titleHeader);
    teamButton->setFixedHeight(MainTheme::RowHeight);
    nameButton = new QPushButton("Name", titleHeader);
    nameButton->setFixedHeight(MainTheme::RowHeight);
    ageButton = new QPushButton("Age", titleHeader);
    ageButton->setFixedHeight(MainTheme::RowHeight);
    pointsButton = new QPushButton("Points", titleHeader);
    pointsButton->setFixedHeight(MainTheme::RowHeight);


    titleHeaderLayout->addWidget(nameButton);
    titleHeaderLayout->addWidget(ageButton);
    titleHeaderLayout->addWidget(teamButton);
    titleHeaderLayout->addWidget(pointsButton);

    connectTitleButtons();


    // setup main list view
    mainLayout->addWidget(controlHeader);
    mainLayout->addWidget(titleHeader);
    mainLayout->addWidget(driversListView);
    listViewWrapper->setLayout(mainLayout);

    driversCard = new DriversCard(this);
    addWidget(listViewWrapper);
    addWidget(driversCard);
    setCurrentIndex(0);

    connect(addDriverButton, &QPushButton::clicked, this, &DriversView::showAddDriverDialog);
    connect(driversListView, &QListView::clicked, this, [&](const QModelIndex& index) {
        QModelIndex sourceIndex = sortProxyModel->mapToSource(index);
        int selectedDriverId = driversModel->data(sourceIndex, DriversModel::IdRole).toInt();
        driversCard->setDriver(QSharedPointer<Driver>(DriverController::getById(selectedDriverId)));
        setCurrentIndex(1);
    });

    connect(driversCard, &DriversCard::closeCart, this, [this]() {
        setCurrentIndex(0);
    });

    connect(driversCard, &DriversCard::driverUpdated, this, [&](QSharedPointer<Driver> driver) {
            int row = driversModel->findItemRow(driver->id(), DriversModel::IdRole); // Предполагаем, что метод findDriverRow возвращает индекс гонщика по ID
            if (row != -1) driversModel->updateItem(row, driver);
            setCurrentIndex(0);
    });

    connect(driversCard, &DriversCard::driverDeleted, this, [&](int deletedDriverId) {
            int row = driversModel->findItemRow(deletedDriverId, DriversModel::IdRole);
            if(row != -1) driversModel->removeItem(row);
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
            driversModel->addItem(newDriver);
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", e.what());
        }
    }
}

void DriversView::connectTitleButtons() {
    connect(nameButton, &QPushButton::clicked, this, [&]() {
        if(sortProxyModel!=nullptr) {
            sortProxyModel->setSortRole(DriversModel::NameRole);
            nameInc = !nameInc;
            auto sortOrder = nameInc ? Qt::AscendingOrder : Qt::DescendingOrder;
            sortProxyModel->sort(0, sortOrder);
        }
    });

    connect(ageButton, &QPushButton::clicked, this, [&]() {
        if(sortProxyModel!=nullptr) {
            sortProxyModel->setSortRole(DriversModel::AgeRole);
            ageInc = !ageInc;
            auto sortOrder = ageInc ? Qt::AscendingOrder : Qt::DescendingOrder;
            sortProxyModel->sort(0, sortOrder);
        }
    });
    connect(teamButton, &QPushButton::clicked, this, [&]() {
        if(sortProxyModel!=nullptr) {
            sortProxyModel->setSortRole(DriversModel::TeamRole);
            teamInc = !teamInc;
            auto sortOrder = teamInc ? Qt::AscendingOrder : Qt::DescendingOrder;
            sortProxyModel->sort(0, sortOrder);
        }
    });

    connect(pointsButton, &QPushButton::clicked, this, [&]() {
        if(sortProxyModel!=nullptr) {
            sortProxyModel->setSortRole(DriversModel::PointsRole);
            pointsInc = !pointsInc;
            auto sortOrder = pointsInc ? Qt::AscendingOrder : Qt::DescendingOrder;
            sortProxyModel->sort(0, sortOrder);
        }
    });
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
    addDriverButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout->addWidget(addDriverButton);
    row->setLayout(layout);




    return row;
}
