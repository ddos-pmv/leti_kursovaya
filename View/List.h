//
// Created by Сергей Перлин on 22.12.2024.
//

#ifndef MAINSIDEBAR_H
#define MAINSIDEBAR_H

#include <QListWidget>
#include <QStringList>

#include "MainThemeVars.h"


class List : public QListWidget{
    Q_OBJECT
public:
    explicit List(const QString& objName, QWidget* parent = nullptr);
    void setupItems(const QStringList& items);


};



#endif //MAINSIDEBAR_H
