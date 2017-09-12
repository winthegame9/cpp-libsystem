#include "borrowerregister.h"
#include "ui_borrowerregister.h"
#include "dialogs/persondialog.h"
#include <QMessageBox>
#include <QDebug>

BorrowerRegister::BorrowerRegister(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BorrowerRegister)
{
    ui->setupUi(this);

    listModel = new PersonListModel(lib::Borrower, this);
    ui->listView->setModel(listModel);

    setDeregisterButtonEnabled(false);

    connect(this, &BorrowerRegister::itemInsert,
            listModel, &PersonListModel::whenItemInserted);
    connect(this, &BorrowerRegister::itemUpdate,
            listModel, &PersonListModel::whenItemUpdated);
}

BorrowerRegister::~BorrowerRegister()
{
    delete ui;
}

void BorrowerRegister::setDeregisterButtonEnabled(bool enable)
{
    ui->buttonDeregister->setEnabled(enable);
}

lib::Person BorrowerRegister::getCurrent() const
{
    return current;
}

void BorrowerRegister::loadFromDB(QVector<lib::Person> items)
{
    if(items.size() > 0) {
        qDebug() << "loading borrowers from database";
        listModel->loadFromDB(items);
    }
    qDebug() << "no borrowers from database";
}

void BorrowerRegister::on_listView_clicked(const QModelIndex &index)
{
    current = index.data(Qt::UserRole).value<lib::Person>();

    if(current.getDeregistered().isValid()) {
        setDeregisterButtonEnabled(false);
    } else {
        setDeregisterButtonEnabled(true);
    }

    emit itemSelectionChanged(current);
}

void BorrowerRegister::on_buttonRegister_clicked()
{
    // create a dialog for role lib::Borrower
    PersonDialog dialog(lib::Borrower, this);

    connect(&dialog, &PersonDialog::personCreated,
            this, &BorrowerRegister::whenPersonCreated);

    dialog.exec();
}

void BorrowerRegister::on_buttonDeregister_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,
                                  tr("Deregister person"),
                                  tr("Deregister selected person?"),
                                  QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes) {
        current.setDeregistered(QDate::currentDate());
        setDeregisterButtonEnabled(false);
        emit itemUpdate(current);
    }
}

void BorrowerRegister::whenPersonCreated(lib::Person person)
{
    emit itemInsert(person);
}

void BorrowerRegister::whenPersonInsertedFromMain(lib::Person person)
{
    emit itemInsert(person);
}
