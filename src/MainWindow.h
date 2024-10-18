#include <QMainWindow>
#include <QListWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QPixmap>
#include <QLabel>
#include <QWidget>
#include <QSpacerItem>
#include "Views/DriversListView.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        setAttribute(Qt::WA_TranslucentBackground, true);

        // Main widget
        QWidget *centralWidget = new QWidget(this);
        centralWidget->setContentsMargins(0, 0, 0, 0);
        centralWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
        mainLayout->setAlignment(Qt::AlignCenter);

        setCentralWidget(centralWidget);

        // Set background image
        updateBackgroundImage();

        // Sidebar (left)
        QVBoxLayout *sidebarLayout = new QVBoxLayout();
        sidebarLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));  // Add expanding space at the top

        QListWidget *sidebar = new QListWidget(centralWidget);
        sidebar->setFixedWidth(300);
        sidebar->addItem("Home");
        sidebar->addItem("Drivers");
        sidebar->addItem("Tracks");

        sidebarLayout->addWidget(sidebar);
        sidebarLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));  // Add expanding space at the bottom

        // Central content
        QVBoxLayout *centralContentLayout = new QVBoxLayout();
        centralContentLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));


        QStackedWidget *content = new QStackedWidget(centralWidget);
        content->setFixedWidth(800);

        // Pages for central content
        QLabel *homePage = new QLabel("hello", content);
        DriversList *driversPage = new DriversList(content);
        QLabel *tracksPage = new QLabel("hello4", content);

        content->addWidget(homePage);
        content->addWidget(driversPage);
        content->addWidget(tracksPage);

        centralContentLayout->addWidget(content);
        centralContentLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding)); // Add expanding space at the bottom

        mainLayout->addLayout(sidebarLayout);
        mainLayout->addLayout(centralContentLayout);

        mainLayout->setSpacing(0);
        mainLayout->setMargin(0);

        // Connect sidebar to central content
        connect(sidebar, &QListWidget::currentRowChanged, content, &QStackedWidget::setCurrentIndex);
        connect(sidebar, &QListWidget::itemDoubleClicked, driversPage, &DriversList::onDriverMenuDoubleClicked);

        setStyleSheet(R"(
            QMainWindow {
                margin: 0;
                padding: 0;
            }
            QWidget {
                margin: 0;
                padding: 0;
            }
            QListWidget {
                background-image: none;
                background-color: transparent;
                font-size: 14px;
            }
            QListWidget::item {
                color: rgba(255, 255, 255, 0.8);
                background-color: rgba(58, 58, 58, 0.7);
                padding: 5px 0;
                margin-top: 5px;
            }
            QListWidget::item:selected {
                background-color: white;
                color: black;
            }
            QListWidget::item:hover {
                color: white;
                background-color: rgb(255, 0, 102);
            }
        )");
    }

protected:
    void resizeEvent(QResizeEvent *event) override {
        QMainWindow::resizeEvent(event);
        updateBackgroundImage();
    }

private:
    void updateBackgroundImage() {
        QPixmap bgPixmap("/Users/sergejperlin/CLionProjects/OOPQt/src/public/bg.png");
        QPalette palette;
        palette.setBrush(QPalette::Window, QBrush(bgPixmap.scaled(size().width(), size().height(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation)));
        centralWidget()->setAutoFillBackground(true);
        centralWidget()->setPalette(palette);
    }
};