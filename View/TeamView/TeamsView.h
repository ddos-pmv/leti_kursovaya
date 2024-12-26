#ifndef TEAMSVIEW_H
#define TEAMSVIEW_H

#include <QStackedWidget>
#include <QListView>
#include <QSortFilterProxyModel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>

#include "../../Entities/Team.h"
#include "../../Controllers/TeamController.h"
#include "../../Models/TeamsModel.h"
#include "TeamsDelegate.h"
#include "../MainThemeVars.h"
// #include "TeamsCard.h"

class TeamsView : public QStackedWidget {
    public:
        explicit TeamsView(QWidget* parent = nullptr);
        const TeamsModel* model() const{return teamsModel;}
        const QListView* listView() const{return teamsListView;}

private:
    QWidget* listViewWrapper;

    QWidget* controlHeader;
    QPushButton* addBtn;
    QPushButton* removeBtn;

    QWidget* titleHeader;
    QHBoxLayout* titleHeaderLayout;

    QPushButton* nameButton;
    QPushButton* driversColButton;
    QPushButton* pointsSumButton;

    bool nameInc = true;
    bool driversColInc = true;
    bool pointsSumInc = true;

    QListView* teamsListView;
    TeamsModel* teamsModel;
    // TeamsCard* teamsCard;
    QSortFilterProxyModel* sortProxyModel;

    void setStyleSheetForListView(QListView* listView);
    void showDialog();
    void connectTitleButtons();
    QWidget* createControlHeader(QWidget* parent = nullptr);


};
#endif //TEAMSVIEW_H
