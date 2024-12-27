#ifndef RACE_H
#define RACE_H

#include <QObject>
#include <QString>
#include <QDateTime>


class Race : public QObject {
    int m_id;
    QString m_name;
    QDateTime m_date;

public:
    Race(int id, const QString &name, const QDateTime &date, QObject *parent = nullptr);

    Race(const QString& name, const QDateTime& date, QObject* parent = nullptr);

    uint id() const;
    QString name() const;
    QDateTime date() const;

    void setId(int id);
    void setName(const QString& teamName);
    void setDate(const QDateTime& date);
};



#endif //RACE_H
