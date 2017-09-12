#ifndef LOANREGISTRATION_H
#define LOANREGISTRATION_H

#include <QWidget>
#include <QDate>
#include "types/t_book.h"
#include "types/t_person.h"
#include "types/t_loanitem.h"

namespace Ui {
class LoanRegistration;
}

class LoanRegistration : public QWidget
{
    Q_OBJECT

    lib::Book selectedBook;
    lib::Person selectedBorrower;
    lib::Person selectedLibrarian;

    void setOutDateField();
    void setDueDateField(int days);

public:
    explicit LoanRegistration(QWidget *parent = 0);
    ~LoanRegistration();

signals:
    void newLoanRegistered(lib::LoanItem item);

private slots:
    void on_buttonSave_clicked();

    void on_buttonReset_clicked();

    void on_edit_loanTime_valueChanged(int arg1);

public slots:
    void whenCurrentBookChanged(lib::Book book);

    void whenCurrentBorrowerChanged(lib::Person borrower);

    void whenCurrentLibrarianChanged(lib::Person librarian);

private:
    Ui::LoanRegistration *ui;
};

#endif // LOANREGISTRATION_H
