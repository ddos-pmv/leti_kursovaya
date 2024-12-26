#include "List.h"

List::List(const QString& objName, QWidget *parent) : QListWidget(parent) {
    setObjectName(objName);
    setStyleSheet(QString(R"(
        QListWidget#%8 {
            background-color: transparent;
            border: none;
        }
        QListWidget#%8::item {
            height:%1;
            background-color: %2;
            color: %3;
        }
        QListWidget#%8::item:hover {
            background-color: %4;
            color: %5;
        }
        QListWidget#%8::item:selected {
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
        MainTheme::SidebarSelectedTextColor.name(),
        objName
        ));
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setCurrentRow(0);
}

void List::setupItems(const QStringList &items) {
    for (const auto& item : items) {
        addItem(item);
    }
}
