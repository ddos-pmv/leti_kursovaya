#include "Team.h"

Team::Team(int id, const QString& name, int drivers, int pointsSum, QObject* parent) : QObject(parent), m_id(id), m_name(name), m_driversCol(drivers), m_pointsSum(pointsSum) {};
Team::Team(const QString& name, int drivers, int pointsSum, QObject* parent) : QObject(parent), m_name(name), m_driversCol(drivers), m_pointsSum(pointsSum) {};

uint Team::id() const {return m_id;}
QString Team::name() const {return m_name;}
int Team::driversCol() const {return m_driversCol;}

int Team::pointsSum() const { return m_pointsSum;}

void Team::setId(int id) {m_id = id;}
void Team::setName(const QString& teamName) {m_name = teamName;}
void Team::setDriversCol(int driversCol) {m_driversCol = driversCol;}
void Team::setPointsSum(int pointsSum) { m_pointsSum = pointsSum;}
