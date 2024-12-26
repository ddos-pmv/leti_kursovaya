#ifndef TEAMSMODEL_H
#define TEAMSMODEL_H

#include "BaseListModel.h"
#include "../Entities/Team.h"
#include "../Controllers/TeamController.h"
#include "../UpdateManager.h"

class TeamsModel : public BaseListModel<Team> {
    Q_OBJECT
public:
    enum TeamRoles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        DriversColRole,
        PointsSumRole
    };

    explicit TeamsModel(QObject* parent = nullptr)
        : BaseListModel(parent) {
        m_roleNames[IdRole] = "id";
        m_roleNames[NameRole] = "name";
        m_roleNames[DriversColRole] = "driversCol";
        m_roleNames[PointsSumRole] = "pointsSum";

        connect(UpdateManager::instance(), &UpdateManager::driversUpdated, this, &TeamsModel::loadItemsFromDatabase);
    }

    QVariant dataForRole(const QSharedPointer<Team>& item, int role) const override {
        switch (role) {
            case IdRole: return item->id();
            case NameRole: return item->name();
            case DriversColRole: return item->driversCol();
            case PointsSumRole: return item->pointsSum();
            default: return {};
        }
    }

    void loadItemsFromDatabase() override {
        // Очищаем текущую модель
        clearItems();

        // Загружаем все элементы из контроллера
        QVector<QSharedPointer<Team>> teams = TeamController::all();

        // Добавляем элементы в модель
        for (auto& team : teams) {
            addItem(team);
        }
    }
};

#endif // TEAMSMODEL_H
