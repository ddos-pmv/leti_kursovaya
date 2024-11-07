// DriverTableModel.h
#include <QAbstractTableModel>
#include <QVector>
#include "Entities/Driver.h"

class DriverTableModel : public QAbstractTableModel {
    Q_OBJECT
public:
    DriverTableModel(QObject *parent = nullptr);

    // Реализация методов для модели
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Метод для установки данных модели
    void setDrivers(const QVector<Driver> &drivers);

private:
    QVector<Driver> m_drivers;
};
