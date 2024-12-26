#include "TeamsView.h"

#include "AddTeamsDialog.h"

TeamsView::TeamsView(QWidget* parent) : QStackedWidget(parent) {
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

    teamsListView = new QListView(this);
    teamsModel = new TeamsModel(this);
    setStyleSheetForListView(teamsListView);

    sortProxyModel = new QSortFilterProxyModel(this);
    sortProxyModel->setSortRole(TeamsModel::IdRole);
    sortProxyModel->setSourceModel(teamsModel);

    teamsListView->setModel(sortProxyModel);
    teamsListView->setMouseTracking(true);
    teamsListView->setItemDelegate(new TeamsDelegate(this));
    teamsListView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    teamsListView->setSpacing(MainTheme::RowMargin);



    controlHeader = createControlHeader(listViewWrapper);


    // setup title header
    titleHeader = new QWidget(listViewWrapper);
    titleHeader->setContentsMargins(0,0,0,0);
    titleHeader->setStyleSheet("QPushButton{ background-color: white; color: black;}");
    titleHeaderLayout = new QHBoxLayout(titleHeader);
    titleHeaderLayout->setSpacing(MainTheme::RowMargin);
    titleHeader->setContentsMargins(0,0,0,0);
    titleHeader->setLayout(titleHeaderLayout);

    nameButton = new QPushButton("Team name", titleHeader);
    nameButton->setFixedHeight(MainTheme::RowHeight);
    driversColButton = new QPushButton("Drivers amount", titleHeader);
    driversColButton->setFixedHeight(MainTheme::RowHeight);
    pointsSumButton = new QPushButton("Points sum", titleHeader);
    pointsSumButton->setFixedHeight(MainTheme::RowHeight);

    titleHeaderLayout->addWidget(nameButton);
    titleHeaderLayout->addWidget(driversColButton);
    titleHeaderLayout->addWidget(pointsSumButton);



    mainLayout->addWidget(controlHeader);
    mainLayout->addWidget(titleHeader);
    mainLayout->addWidget(teamsListView);

    listViewWrapper->setLayout(mainLayout);

    QVector<QSharedPointer<Team>> items = TeamController::all();

    for(auto& item : items) {
        teamsModel->addItem(item);
    }

    addWidget(listViewWrapper);
    // addWidget(driversCard);
    setCurrentIndex(0);
    connectTitleButtons();
    connect(addBtn, &QPushButton::clicked, this, &TeamsView::showDialog);
}


void TeamsView::setStyleSheetForListView(QListView* listView) {
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

void TeamsView::showDialog() {
    AddTeamsDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {
        QString teamName = dialog.getTeamName();

        try {
            TeamController::validateTeamName(teamName);
            int id = TeamController::add(teamName);

            QSharedPointer<Team> newTeam = TeamController::get(id);
            teamsModel->addItem(newTeam);
        } catch (const std::exception& e) {
            QMessageBox::critical(this, "Error", e.what());
        }
    }
}

void TeamsView::connectTitleButtons() {
    connect(nameButton, &QPushButton::clicked, this, [&]() {
        if(sortProxyModel!=nullptr) {
            sortProxyModel->setSortRole(TeamsModel::NameRole);
            nameInc = !nameInc;
            auto sortOrder = nameInc ? Qt::AscendingOrder : Qt::DescendingOrder;
            sortProxyModel->sort(0, sortOrder);
        }
    });

    connect(driversColButton, &QPushButton::clicked, this, [&]() {
        if(sortProxyModel!=nullptr) {
            sortProxyModel->setSortRole(TeamsModel::DriversColRole);
            driversColInc = !driversColInc;
            auto sortOrder = driversColInc ? Qt::AscendingOrder : Qt::DescendingOrder;
            sortProxyModel->sort(0, sortOrder);
        }
    });
    connect(pointsSumButton, &QPushButton::clicked, this, [&]() {
        if(sortProxyModel!=nullptr) {
            sortProxyModel->setSortRole(TeamsModel::PointsSumRole);
            pointsSumInc = !pointsSumInc;
            auto sortOrder = pointsSumInc ? Qt::AscendingOrder : Qt::DescendingOrder;
            sortProxyModel->sort(0, sortOrder);
        }
    });
}

QWidget* TeamsView::createControlHeader(QWidget *parent) {
    auto row = new QWidget(parent);
    auto layout = new QHBoxLayout(row);
    layout->setContentsMargins(0,0,0,0);

    row->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    row->setFixedHeight(MainTheme::RowHeight);

    row->setStyleSheet("QPushButton{"
                       "background-color: white;"
                       "color: black;"
                       "}");

    addBtn = new QPushButton("+", parent);
    // sortByName = new QPushButton("By name", parent);

    layout->addWidget(addBtn);
    row->setLayout(layout);

    return row;
}
