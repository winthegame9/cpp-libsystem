#include "loanregistration.h"
#include "ui_loanregistration.h"

LoanRegistration::LoanRegistration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoanRegistration)
{
    ui->setupUi(this);

    ui->edit_outDate->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui->edit_dueDate->setButtonSymbols(QAbstractSpinBox::NoButtons);

    // set current date as out date
    setOutDateField();
    // set due date to current date + default spinbox value
    setDueDateField(ui->edit_loanTime->value());
}

LoanRegistration::~LoanRegistration()
{
    delete ui;
}

void LoanRegistration::setOutDateField()
{
    ui->edit_outDate->setDate(QDate::currentDate());
}

void LoanRegistration::setDueDateField(int days)
{
    QDate date = ui->edit_outDate->date().addDays(days);
    ui->edit_dueDate->setDate(date);
}

void LoanRegistration::on_buttonSave_clicked()
{
    selectedBook.setLoaned(1);
    lib::LoanItem item(selectedBook,
                       selectedBorrower,
                       selectedLibrarian);
    item.setDueDate(ui->edit_dueDate->date());
    if(item.isValid()) {
        emit newLoanRegistered(item);
        whenCurrentBookChanged(lib::Book());
    }
}

void LoanRegistration::on_buttonReset_clicked()
{
    whenCurrentBookChanged(lib::Book());
    whenCurrentBorrowerChanged(lib::Person());
    whenCurrentLibrarianChanged(lib::Person());
}

void LoanRegistration::on_edit_loanTime_valueChanged(int arg1)
{
    setDueDateField(arg1);
}

void LoanRegistration::whenCurrentBookChanged(lib::Book book)
{
    selectedBook = book;
    ui->edit_isbn->setText(selectedBook.getISBN());
    ui->edit_author->setText(selectedBook.getAuthor());
    ui->edit_title->setText(selectedBook.getTitle());
}

void LoanRegistration::whenCurrentBorrowerChanged(lib::Person borrower)
{
    selectedBorrower = borrower;
    ui->edit_borrower->setText(selectedBorrower.getFullname());
    ui->edit_address->setText(selectedBorrower.getAddress());
}

void LoanRegistration::whenCurrentLibrarianChanged(lib::Person librarian)
{
    selectedLibrarian = librarian;
    ui->edit_librarian->setText(selectedLibrarian.getFullname());
}
