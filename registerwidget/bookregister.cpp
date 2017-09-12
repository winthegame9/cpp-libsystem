#include "bookregister.h"
#include "ui_bookregister.h"
#include "dialogs/bookdialog.h"
#include <QMessageBox>
#include <QDebug>

BookRegister::BookRegister(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BookRegister)
{
    ui->setupUi(this);

    listModel = new BookListModel(this);
    ui->listView->setModel(listModel);

    connect(this, &BookRegister::itemInsert,
            listModel, &BookListModel::whenItemInserted);
    connect(this, &BookRegister::itemRemove,
            listModel, &BookListModel::whenItemRemoved);
    connect(this, &BookRegister::itemUpdate,
            listModel, &BookListModel::whenItemUpdated);
}

BookRegister::~BookRegister()
{
    delete ui;
}

lib::Book BookRegister::getCurrent() const
{
    return current;
}

void BookRegister::loadFromDB(QVector<lib::Book> books)
{
    if(books.size() > 0) {
        qDebug() << "loading books from database";
        listModel->loadFromDB(books);
    }
    qDebug() << "no books from database";
}

void BookRegister::on_listView_clicked(const QModelIndex &index)
{
    // retrieve the book from index argument
    current = index.data(Qt::UserRole).value<lib::Book>();
    emit itemSelectionChanged(current);
}

void BookRegister::on_buttonCreate_clicked(void)
{
    // display book create dialog
    BookDialog dialog(this);

    connect(&dialog, &BookDialog::bookCreated,
            this, &BookRegister::whenBookCreated);

    dialog.exec();
}

void BookRegister::on_buttonRemove_clicked(void)
{
    // display remove messagebox
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,
                                  tr("Book removal"),
                                  tr("Are you sure you want to remove the selected book?"),
                                  QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes) {
        emit itemRemove(current);
    }
}

void BookRegister::whenBookCreated(lib::Book book)
{
    emit itemInsert(book);
}

void BookRegister::whenBookStatusUpdated(lib::Book book)
{
    emit itemUpdate(book);
}

void BookRegister::whenBookInsertFromMain(lib::Book book)
{
    emit itemInsert(book);
}
