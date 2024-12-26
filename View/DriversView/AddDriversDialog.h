#ifndef ADDDRIVERDIALOG_H
#define ADDDRIVERDIALOG_H

#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QDialogButtonBox>
#include "../../Entities/Driver.h"

class AddDriverDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddDriverDialog(QWidget* parent = nullptr)
        : QDialog(parent), nameEdit(new QLineEdit(this)), ageEdit(new QLineEdit(this)), teamEdit(new QLineEdit(this)) {
        setWindowTitle("Add New Driver");

        QFormLayout* formLayout = new QFormLayout(this);
        formLayout->addRow("Name:", nameEdit);
        formLayout->addRow("Age:", ageEdit);
        formLayout->addRow("Team:", teamEdit);

        QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
        formLayout->addWidget(buttonBox);

        connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
        connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    }

    QString getName() const { return nameEdit->text(); }
    int getAge() const { return ageEdit->text().toInt(); }
    QString getTeam() const { return teamEdit->text(); }

private:
    QLineEdit* nameEdit;
    QLineEdit* ageEdit;
    QLineEdit* teamEdit;
};

#endif // ADDDRIVERDIALOG_H
