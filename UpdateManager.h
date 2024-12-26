//
// Created by Сергей Перлин on 26.12.2024.
//

#ifndef UPDATEMANAGER_H
#define UPDATEMANAGER_H

#include <QObject>


class UpdateManager : public QObject {
    Q_OBJECT
public:
    static UpdateManager* instance();

    void teamsInfoUpdated();

    void driversInfoUpdated();


signals:
    void teamsUpdated();
    void driversUpdated();


private:
    explicit UpdateManager(QObject* parent);
    static UpdateManager* m_instance;

};



#endif //UPDATEMANAGER_H
