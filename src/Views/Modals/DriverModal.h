#ifndef DRIVERMODAL_H
#define DRIVERMODAL_H

#include <QVBoxLayout>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QDialog>


class DriverModal : public QDialog {
    Q_OBJECT

public:
    DriverModal(QWidget *parent = nullptr) : QDialog(parent){
        QVBoxLayout *layout = new QVBoxLayout(this);

        QLineEdit *nameEdit = new QLineEdit(this);
        nameEdit->setText("Name");

        QLineEdit *ageEdit = new QLineEdit(this);
        ageEdit->setText("Age");

        QLineEdit *teamEdit = new QLineEdit(this);
        teamEdit->setText("Team");

        QLineEdit *pointsEdit = new QLineEdit(this);
        pointsEdit->setText("Points");

        QPushButton *addBtn = new QPushButton("Add", this);

        layout->addWidget(nameEdit);
        layout->addWidget(ageEdit);
        layout->addWidget(teamEdit);
        layout->addWidget(pointsEdit);
        layout->addWidget(addBtn);

        connect(addBtn, &QPushButton::clicked, this, &DriverModal::addDriver);

    }

private slots:
    void addDriver() {
        qDebug() << "Driver added\n";
        accept();
    }

};

#endif //DRIVERMODAL_H
