//
// Created by Сергей Перлин on 27.12.2024.
//

#ifndef RACESMODEL_H
#define RACESMODEL_H

#include <QSharedPointer>
#include <QObject>

#include "BaseListModel.h"
#include "../Entities/Race.h"
#include "../Controllers/RaceController.h"

class RacesModel :  public BaseListModel<Race> {
    Q_OBJECT
public:
    enum DriverRoles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        DateRole,
    };

    explicit RacesModel(QObject* parent = nullptr)
        : BaseListModel(parent) {
        m_roleNames[IdRole] = "id";
        m_roleNames[NameRole] = "name";
        m_roleNames[DateRole] = "date";

        loadItemsFromDatabase();
    }

    QVariant dataForRole(const QSharedPointer<Race>& item, int role) const override {
        switch (role) {
            case IdRole: return item->id();
            case NameRole: return item->name();
            case DateRole: return item->date();
            default: return {};
        }
    }


    void loadItemsFromDatabase() override {
        // Очищаем текущую модель
        clearItems();

        // Загружаем все элементы из контроллера
        QVector<QSharedPointer<Race>> races = RaceController::all();

        // Добавляем элементы в модель
        for (auto& race : races) {
            addItem(race);
        }
    }
};



#endif //RACESMODEL_H
