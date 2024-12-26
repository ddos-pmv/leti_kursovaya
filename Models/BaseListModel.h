#ifndef BASELISTMODEL_H
#define BASELISTMODEL_H

#include <QAbstractListModel>
#include <QSharedPointer>
#include <QVector>

template<typename T>
class BaseListModel : public QAbstractListModel {
public:
    explicit BaseListModel(QObject* parent = nullptr)
        : QAbstractListModel(parent) {}

    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        Q_UNUSED(parent);
        return m_items.size();
    }

    QHash<int, QByteArray> roleNames() const override {
        return m_roleNames;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (!index.isValid() || index.row() >= m_items.size()) {
            return {};
        }

        auto item = m_items[index.row()];
        return dataForRole(item, role);
    }

    virtual QVariant dataForRole(const QSharedPointer<T>& item, int role) const = 0;

    void addItem(QSharedPointer<T> item) {
        beginInsertRows(QModelIndex(), m_items.size(), m_items.size());
        m_items.append(item);
        endInsertRows();
    }

    void updateItem(int row, QSharedPointer<T> item) {
        if (row >= 0 && row < m_items.size()) {
            m_items[row] = item;
            emit dataChanged(index(row), index(row));
        }
    }

    void removeItem(int row) {
        if (row >= 0 && row < m_items.size()) {
            beginRemoveRows(QModelIndex(), row, row);
            m_items.removeAt(row);
            endRemoveRows();
        }
    }

    void clearItems() {
        beginResetModel();
        m_items.clear();
        endResetModel();
    }

    int findItemRow(int id, int curRole) const {
        for (int i = 0; i < m_items.size(); ++i) {
            if (data(index(i), curRole) == id) {
                return i;
            }
        }
        return -1;
    }

public slots:
    virtual void loadItemsFromDatabase() = 0;

protected:
    QVector<QSharedPointer<T>> m_items;
    QHash<int, QByteArray> m_roleNames;
};

#endif // BASELISTMODEL_H
