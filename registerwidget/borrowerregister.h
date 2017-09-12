#ifndef BORROWERREGISTER_H
#define BORROWERREGISTER_H

#include <QWidget>
#include "listmodels/personlistmodel.h"
#include "types/t_person.h"

namespace Ui {
class BorrowerRegister;
}

class BorrowerRegister : public QWidget
{
    Q_OBJECT

    PersonListModel *listModel;
    lib::Person current;

    void setDeregisterButtonEnabled(bool enable);

public:
    explicit BorrowerRegister(QWidget *parent = 0);
    ~BorrowerRegister();

    lib::Person getCurrent() const;
    void loadFromDB(QVector<lib::Person> items);

signals:
    void itemSelectionChanged(lib::Person person);
    void itemInsert(lib::Person person);
    void itemUpdate(lib::Person person);
    void itemRemove(lib::Person person);

private slots:
    void on_listView_clicked(const QModelIndex &index);

    void on_buttonRegister_clicked();

    void on_buttonDeregister_clicked();

    void whenPersonCreated(lib::Person person);

public slots:
    void whenPersonInsertedFromMain(lib::Person person);

private:
    Ui::BorrowerRegister *ui;
};

#endif // BORROWERREGISTER_H
