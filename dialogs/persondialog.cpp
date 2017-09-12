#include "persondialog.h"
#include "ui_persondialog.h"
#include <QPushButton>
#include <QDialogButtonBox>

PersonDialog::PersonDialog(lib::PersonRole role, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PersonDialog)
{
    ui->setupUi(this);

    // this dialog can create a person of either
    // Borrower or Librarian
    roleSelection = role;

    // set default registered date to today
    ui->edit_registered->setDate(QDate::currentDate());

    // disable save button
    setSaveButtonEnabled(false);

    // connect signals
    connect(ui->edit_firstname, &QLineEdit::textChanged, this, &PersonDialog::checkLineEdits);
    connect(ui->edit_lastname, &QLineEdit::textChanged, this, &PersonDialog::checkLineEdits);
    connect(ui->edit_address, &QLineEdit::textChanged, this, &PersonDialog::checkLineEdits);
    connect(ui->edit_registered, &QDateEdit::dateChanged, this, &PersonDialog::checkLineEdits);
}

PersonDialog::~PersonDialog()
{
    delete ui;
}

void PersonDialog::setSaveButtonEnabled(bool enable)
{
    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(enable);
}

void PersonDialog::checkLineEdits()
{
    bool enable = !ui->edit_firstname->text().isEmpty()
            && !ui->edit_lastname->text().isEmpty()
            && !ui->edit_address->text().isEmpty()
            && !(ui->edit_registered->date() > QDate::currentDate());

    setSaveButtonEnabled(enable);
}

void PersonDialog::on_buttonBox_accepted()
{
    lib::Person person(ui->edit_firstname->text(),
                       ui->edit_lastname->text(),
                       ui->edit_address->text(),
                       ui->edit_registered->date(),
                       this->roleSelection);
    /*
    person.setFirstname(ui->edit_firstname->text());
    person.setLastname(ui->edit_lastname->text());
    person.setAddress(ui->edit_address->text());
    person.setRegistered(ui->edit_registered->date());
    person.setRole(this->roleSelection);
    */
    emit personCreated(person);
}
