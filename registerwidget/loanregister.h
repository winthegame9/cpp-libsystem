#ifndef LOANREGISTER_H
#define LOANREGISTER_H

#include <QWidget>
#include "listmodels/loanlistmodel.h"
#include "types/t_loanitem.h"
#include "types/t_book.h"

namespace Ui {
class LoanRegister;
}

class LoanRegister : public QWidget
{
    Q_OBJECT

    LoanListModel *listModel;
    lib::LoanItem current;

    void setButtonsEnabled(bool enable);

public:
    explicit LoanRegister(QWidget *parent = 0);
    ~LoanRegister();

    lib::LoanItem getCurrent() const;
    void loadFromDB(QVector<lib::LoanItem> items);

signals:
    void itemSelectionChanged(lib::LoanItem item);
    void itemInsert(lib::LoanItem item);
    void itemUpdate(lib::LoanItem item);
    void itemRemove(lib::LoanItem item);
    void bookStatusChanged(lib::Book book);

public slots:
    void whenLoanRegistered(lib::LoanItem item);

private slots:
    void on_listView_clicked(const QModelIndex &index);

    void on_buttonReturn_clicked(void);

    void on_buttonExtend_clicked(void);

private:
    Ui::LoanRegister *ui;
};

#endif // LOANREGISTER_H
