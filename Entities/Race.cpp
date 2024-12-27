#include "Race.h"

Race::Race(int id, const QString &name, const QDateTime &date, QObject *parent):
QObject(parent), m_id(id), m_name(name), m_date(date){};

Race::Race(const QString& name, const QDateTime& date, QObject* parent)
    :QObject(parent), m_id(-1), m_name(name), m_date(date){};


uint Race::id() const {return m_id;}
QString Race::name() const {return m_name;}
QDateTime Race::date() const {return m_date;}

void Race::setId(int id) {m_id = id;}
void Race::setName(const QString& name) {m_name = name;}
void Race::setDate(const QDateTime& date) {m_date = date;}
