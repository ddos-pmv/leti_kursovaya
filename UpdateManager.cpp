
#include "UpdateManager.h"

UpdateManager* UpdateManager::m_instance = nullptr;

UpdateManager* UpdateManager::instance() {
    if (!m_instance) {
        m_instance = new UpdateManager(nullptr);
    }
    return m_instance;
}

void UpdateManager::teamsInfoUpdated() {
    emit teamsUpdated();
}

void UpdateManager::driversInfoUpdated() {
    emit driversUpdated();
}

void UpdateManager::tracksInfoUpdated() {
    emit tracksUpdated();
}

UpdateManager::UpdateManager(QObject *parent) : QObject(parent) {
}
