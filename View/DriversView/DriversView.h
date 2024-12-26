#ifndef DRIVERMAINVIEW_H
#define DRIVERMAINVIEW_H

#include <QStackedWidget>
#include <QWidget>
#include <QListView>
#include <QVBoxLayout>
#include <QListWidget>
#include <QSortFilterProxyModel>


#include "../../Models/DriversModel.h"
#include "DriversDelegate.h"
#include "DriversCard.h"
#include "../../Entities/Driver.h"
#include "../../Controllers/DriverController.h"
#include "../MainThemeVars.h"
#include "AddDriversDialog.h"

class DriversView : public QStackedWidget {
public:
    explicit DriversView(QWidget* parent = nullptr);


    const DriversModel* model() const{return driversModel;}
    const QListView* listView() const{return driversListView;}

private:
    QWidget* listViewWrapper;


    QWidget* controlHeader;
    QWidget* titleHeader;
    QHBoxLayout* titleHeaderLayout;


    QPushButton* addDriverButton;
    QPushButton* teamButton;
    QPushButton* nameButton;
    QPushButton* ageButton;
    QPushButton* pointsButton;

    bool nameInc = true;
    bool ageInc = true;
    bool teamInc = true;
    bool pointsInc = true;

    QListView* driversListView;
    DriversModel* driversModel;
    DriversCard* driversCard;
    QSortFilterProxyModel* sortProxyModel;

    void setStyleSheetForListView(QListView* listView);
    void showAddDriverDialog();
    void connectTitleButtons();
    QWidget* createControlHeader(QWidget* parent = nullptr);

};

#endif //DRIVERMAINVIEW_H
