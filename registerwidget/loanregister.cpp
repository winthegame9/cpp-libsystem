#include "loanregister.h"
#include "ui_loanregister.h"
#include <QDebug>

LoanRegister::LoanRegister(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoanRegister)
{
    ui->setupUi(this);

    listModel = new LoanListModel(this);
    ui->listView->setModel(listModel);

    setButtonsEnabled(false);

    connect(this, &LoanRegister::itemInsert,
            listModel, &LoanListModel::whenIteminserted);
    connect(this, &LoanRegister::itemUpdate,
            listModel, &LoanListModel::whenItemUpdated);
}

LoanRegister::~LoanRegister()
{
    delete ui;
}

void LoanRegister::setButtonsEnabled(bool enable)
{
    ui->buttonExtend->setEnabled(enable);
    ui->buttonReturn->setEnabled(enable);
}

lib::LoanItem LoanRegister::getCurrent() const
{
    return current;
}

void LoanRegister::loadFromDB(QVector<lib::LoanItem> items)
{
    if(items.size() > 0) {
        qDebug() << "loading loan items from database";
        listModel->loadFromDB(items);
    }
    qDebug() << "no loan items from database";
}

void LoanRegister::on_listView_clicked(const QModelIndex &index)
{
    // set current item
    current = index.data(Qt::UserRole).value<lib::LoanItem>();
    // enable buttons
    setButtonsEnabled(true);
    // emit current item signal
    emit itemSelectionChanged(current);
}

void LoanRegister::on_buttonReturn_clicked(void)
{
    // set inDate on item
    current.setInDate(QDate::currentDate());
    lib::Book b = current.getBook();
    b.setLoaned(0);
    current.setBook(b);
    // disable buttons
    setButtonsEnabled(false);
    // emit book update signal
    emit itemUpdate(current);
    emit bookStatusChanged(current.getBook());
}

void LoanRegister::on_buttonExtend_clicked(void)
{
    // extend loan with 7 days
    current.setDueDate(current.getDueDate().addDays(7));
    emit itemUpdate(current);

}

void LoanRegister::whenLoanRegistered(lib::LoanItem item)
{
    // insert the received item in the list
    emit itemInsert(item);
    // emit book status change
    emit bookStatusChanged(item.getBook());
}
