#ifndef AddTeamDialog_H
#define AddTeamDialog_H

#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QDialogButtonBox>
#include "../../Entities/Team.h"

class AddTeamsDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddTeamsDialog(QWidget* parent = nullptr)
        : QDialog(parent), teamNameEdit(new QLineEdit(this)) {
        setWindowTitle("Add New Team");

        QFormLayout* formLayout = new QFormLayout(this);
        formLayout->addRow("Team name:", teamNameEdit);

        QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
        formLayout->addWidget(buttonBox);

        connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
        connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    }

    QString getTeamName() const { return teamNameEdit->text(); }

private:
    QLineEdit* teamNameEdit;
};

#endif // AddTeamDialog_H
