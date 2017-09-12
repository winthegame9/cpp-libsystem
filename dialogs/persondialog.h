#ifndef PERSONDIALOG_H
#define PERSONDIALOG_H

#include <QDialog>
#include "types/t_person.h"

namespace Ui {
class PersonDialog;
}

class PersonDialog : public QDialog
{
    Q_OBJECT

    lib::PersonRole roleSelection;

    void setSaveButtonEnabled(bool enable);

public:
    explicit PersonDialog(lib::PersonRole role = lib::Borrower, QWidget *parent = 0);
    ~PersonDialog();

signals:
    void personCreated(lib::Person person);

private slots:

    void on_buttonBox_accepted();
    void checkLineEdits();

private:
    Ui::PersonDialog *ui;
};

#endif // PERSONDIALOG_H
