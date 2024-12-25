#ifndef DRIVERMAINVIEW_H
#define DRIVERMAINVIEW_H

#include <QStackedWidget>
#include <QWidget>
#include <QListView>
#include <QVBoxLayout>


#include "../../Models/DriversModel.h"
#include "DriversDelegate.h"
#include "DriversCard.h"
#include "../../Entities/Driver.h"
#include "../../Controllers/DriverController.h"
#include "../MainThemeVars.h"

class DriversView : public QStackedWidget {
public:
    explicit DriversView(QWidget* parent = nullptr);


    const DriversModel* model() const{return driversModel;}
    const QListView* listView() const{return driversListView;}

private:
    QWidget* listViewWrapper;

    QListView* driversListView;
    DriversModel* driversModel;
    DriversCard* driversCard;

    void setStyleSheetForListView(QListView* listView);

};

#endif //DRIVERMAINVIEW_H
