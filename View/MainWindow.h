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
#include <QDebug>
#include <QGraphicsEffect>

#include "List.h"
#include "MainThemeVars.h"
#include "StackedWidget.h"

class MainWindow : public QWidget {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

protected:
    void resizeEvent(QResizeEvent* event) override;
private:
    QHBoxLayout* centralLayout;

    QWidget* contentWidget;
    QHBoxLayout* contentLayout;

    List* sidebar;
    QStackedWidget* stackedWidget;

    StackedWidget* driversWidget;

    void setupMainWindow();
    QWidget* createExpandingWidget(QWidget* parent = nullptr);
    void updateBackgroundImage(const QString& bgPath);



};
