#include <QtTest/QtTest>
#include "../Models/DriversModel.h"
#include "../Entities/Driver.h"
#include "../Models/BaseListModel.h"

class TestModel : public QObject {
    Q_OBJECT

private slots:
    void testAddDriver();
    void testFindItemRow();
    // void testUpdateItem();
    // void testRemoveItem();
};

void TestModel::testAddDriver() {
    DriversModel model;
    auto driver = QSharedPointer<Driver>(new Driver(1, "Driver 1", 25, "Team A", 100));
    model.addItem(driver);

    QCOMPARE(model.rowCount(), 1);
    QCOMPARE(model.data(model.index(0), DriversModel::NameRole).toString(), QString("Driver 1"));
}

void TestModel::testFindItemRow() {
    DriversModel model;
    auto driver1 = QSharedPointer<Driver>(new Driver(1, "Driver 1", 25, "Team A", 100));
    auto driver2 = QSharedPointer<Driver>(new Driver(2, "Driver 2", 30, "Team B", 200));
    model.addItem(driver1);
    model.addItem(driver2);

    int row = model.findItemRow(1, DriversModel::IdRole);
    QCOMPARE(row, 0);
}
//
// void TestDriversModel::testUpdateItem() {
//     DriversModel model;
//     auto driver = QSharedPointer<Driver>::create(1, "Driver 1", 25, "Team A", 100);
//     model.addItem(driver);
//
//     auto updatedDriver = QSharedPointer<Driver>::create(1, "Updated Driver", 26, "Team A", 150);
//     model.updateItem(0, updatedDriver);
//
//     QCOMPARE(model.data(model.index(0), DriversModel::NameRole).toString(), QString("Updated Driver"));
//     QCOMPARE(model.data(model.index(0), DriversModel::PointsRole).toInt(), 150);
// }
//
// void TestDriversModel::testRemoveItem() {
//     DriversModel model;
//     auto driver = QSharedPointer<Driver>::create(1, "Driver 1", 25, "Team A", 100);
//     model.addItem(driver);
//
//     model.removeItem(0);
//     QCOMPARE(model.rowCount(), 0);
// }

QTEST_MAIN(TestModel)
#include "test_models.moc"
