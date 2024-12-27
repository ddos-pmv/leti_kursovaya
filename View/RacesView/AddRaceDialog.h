#ifndef ADDRACEDIALOG_H
#define ADDRACEDIALOG_H

#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QDialogButtonBox>

class AddRaceDialog : public QDialog {
    Q_OBJECT

public:
    explicit AddRaceDialog(QWidget* parent = nullptr)
        : QDialog(parent), nameEdit(new QLineEdit(this)), dateTimeEdit(new QDateTimeEdit(this)) {
        setWindowTitle("Add New Race");

        QFormLayout* formLayout = new QFormLayout(this);
        formLayout->addRow("Name:", nameEdit);
        formLayout->addRow("Date and Time:", dateTimeEdit);

        dateTimeEdit->setCalendarPopup(true);
        dateTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm:ss");

        QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
        formLayout->addWidget(buttonBox);

        connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
        connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    }

    QString getName() const { return nameEdit->text(); }
    QDateTime getDateTime() const { return dateTimeEdit->dateTime(); }

private:
    QLineEdit* nameEdit;
    QDateTimeEdit* dateTimeEdit;
};

#endif // ADDRACEDIALOG_H