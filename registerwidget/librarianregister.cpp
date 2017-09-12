#include "librarianregister.h"
#include "ui_librarianregister.h"
#include "dialogs/persondialog.h"
#include <QMessageBox>
#include <QDebug>

LibrarianRegister::LibrarianRegister(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LibrarianRegister)
{
    ui->setupUi(this);

    listModel = new PersonListModel(lib::Librarian, this);
    ui->listView->setModel(listModel);

    setDeregisterButtonEnabled(false);

    connect(this, &LibrarianRegister::itemInsert,
            listModel, &PersonListModel::whenItemInserted);
    connect(this, &LibrarianRegister::itemUpdate,
            listModel, &PersonListModel::whenItemUpdated);
}

LibrarianRegister::~LibrarianRegister()
{
    delete ui;
}

void LibrarianRegister::setDeregisterButtonEnabled(bool enable)
{
    ui->buttonDeregister->setEnabled(enable);
}

lib::Person LibrarianRegister::getCurrent() const
{
    return current;
}

void LibrarianRegister::loadFromDB(QVector<lib::Person> items)
{
    if(items.size() > 0) {
        qDebug() << "loading librarians from database";
        listModel->loadFromDB(items);
    }
    qDebug() << "no librarians from database";
}

void LibrarianRegister::on_listView_clicked(const QModelIndex &index)
{
    current = index.data(Qt::UserRole).value<lib::Person>();

    if(current.getDeregistered().isValid()) {
        setDeregisterButtonEnabled(false);
    } else {
        setDeregisterButtonEnabled(true);
    }

    emit itemSelectionChanged(current);
}

void LibrarianRegister::on_buttonRegister_clicked()
{
    // create a dialog for role lib::Librarian
    PersonDialog dialog(lib::Librarian, this);

    connect(&dialog, &PersonDialog::personCreated,
            this, &LibrarianRegister::whenPersonCreated);

    dialog.exec();
}

void LibrarianRegister::on_buttonDeregister_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,
                                  tr("Fire Librarian"),
                                  tr("Fire the selected librarian?"),
                                  QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes) {
        current.setDeregistered(QDate::currentDate());
        setDeregisterButtonEnabled(false);
        emit itemUpdate(current);
    }
}

void LibrarianRegister::whenPersonCreated(lib::Person person)
{
    emit itemInsert(person);
}

void LibrarianRegister::whenPersonInsertedFromMain(lib::Person person)
{
    emit itemInsert(person);
}
