#include "MainWindow.h"

namespace InitConstants {
    const QString bgImagePath = ":/resources/images/mainWindowBg.jpg";
    const QSize contentWidgetSize = QSize(800, 600);
    const QStringList sidebarItems = {"Drivers", "Teams", "Races"};
}


MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    setupMainWindow();
    centralLayout = new QHBoxLayout(this);
    setLayout(centralLayout);

    sidebar = new List("mainSidebar", this);
    sidebar->setupItems(InitConstants::sidebarItems);
    sidebar->setSpacing(MainTheme::RowMargin);

    driversWidget = new StackedWidget(this);
    // auto tmpWidget = createExpandingWidget(this);

    contentWidget = createExpandingWidget(this);
    contentWidget->setFixedSize(InitConstants::contentWidgetSize);
    contentLayout = new QHBoxLayout(contentWidget);

    contentLayout->addWidget(sidebar, 1);
    contentLayout->addWidget(driversWidget, 3);

    centralLayout->addStretch();
    centralLayout->addWidget(contentWidget);
    centralLayout->addStretch();

    updateBackgroundImage(InitConstants::bgImagePath);
    connect(sidebar, &QListWidget::currentRowChanged, this, [&](int currRow) {
        qDebug() << "Row changed:" << currRow;
        driversWidget->setCurrentIndex(currRow);
    });
}

void MainWindow::setupMainWindow() {
    setAttribute(Qt::WA_StyledBackground, true);
    setContentsMargins(0, 0, 0, 0);
}

QWidget * MainWindow::createExpandingWidget(QWidget *parent) {
    auto widget = new QWidget(parent);
    widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    return widget;
}



void MainWindow::updateBackgroundImage(const QString& bgPath) {
    QPixmap bgPixmap(bgPath);
    QPixmap scaledPixmap = bgPixmap.scaled(size().width(), size().height(),
            Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(scaledPixmap));

    setPalette(palette);
    setAutoFillBackground(true);
}

void MainWindow::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    updateBackgroundImage(InitConstants::bgImagePath);
}

