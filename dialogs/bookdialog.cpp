#include "bookdialog.h"
#include "ui_bookdialog.h"
#include <QPushButton>
#include <QDialogButtonBox>

BookDialog::BookDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BookDialog)
{
    ui->setupUi(this);

    setSaveButtonEnabled(false);

    connect(ui->edit_isbn, &QLineEdit::textChanged, this, &BookDialog::checkLineEdits);
    connect(ui->edit_title, &QLineEdit::textChanged, this, &BookDialog::checkLineEdits);
    connect(ui->edit_author, &QLineEdit::textChanged, this, &BookDialog::checkLineEdits);
}

BookDialog::~BookDialog()
{
    delete ui;
}

void BookDialog::setSaveButtonEnabled(bool enable)
{
    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(enable);
}

void BookDialog::checkLineEdits()
{
    bool enable = !ui->edit_isbn->text().isEmpty()
            && !ui->edit_title->text().isEmpty()
            && !ui->edit_author->text().isEmpty();

    setSaveButtonEnabled(enable);
}

void BookDialog::on_buttonBox_accepted()
{
    lib::Book book;
    book.setISBN(ui->edit_isbn->text());
    book.setTitle(ui->edit_title->text());
    book.setAuthor(ui->edit_author->text());
    book.setPublished(ui->edit_published->date());
    book.setLoaned(0);
    emit bookCreated(book);
}
