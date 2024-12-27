#ifndef DRIVERSMODEL_H
#define DRIVERSMODEL_H

#include "BaseListModel.h"
#include "../Entities/Driver.h"
#include "../Controllers/DriverController.h"
#include <QObject>

#include "../UpdateManager.h"

class DriversModel : public BaseListModel<Driver> {
    Q_OBJECT
public:
    enum DriverRoles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        AgeRole,
        TeamRole,
        PointsRole
    };

    explicit DriversModel(QObject* parent = nullptr)
        : BaseListModel(parent) {
        m_roleNames[IdRole] = "id";
        m_roleNames[NameRole] = "name";
        m_roleNames[AgeRole] = "age";
        m_roleNames[TeamRole] = "team";
        m_roleNames[PointsRole] = "points";

        loadItemsFromDatabase();
        connect(UpdateManager::instance(), &UpdateManager::teamsUpdated, this, &DriversModel::loadItemsFromDatabase);
        connect(UpdateManager::instance(), &UpdateManager::driversUpdated, this, &DriversModel::loadItemsFromDatabase);
    }

    QVariant dataForRole(const QSharedPointer<Driver>& item, int role) const override {
        switch (role) {
            case IdRole: return item->id();
            case NameRole: return item->name();
            case AgeRole: return item->age();
            case TeamRole: return item->team();
            case PointsRole: return item->points();
            default: return {};
        }
    }


    void loadItemsFromDatabase() override {
        // Очищаем текущую модель
        clearItems();

        // Загружаем все элементы из контроллера
        QVector<QSharedPointer<Driver>> drivers = DriverController::all();

        // Добавляем элементы в модель
        for (auto& driver : drivers) {
            addItem(driver);
        }
    }
};

#endif // DRIVERSMODEL_H
