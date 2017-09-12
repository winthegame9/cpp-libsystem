#ifndef LOANLISTMODEL_H
#define LOANLISTMODEL_H

#include <QAbstractListModel>
#include <QVector>
#include "types/t_loanitem.h"

class LoanListModel : public QAbstractListModel
{
    Q_OBJECT

    QVector<lib::LoanItem> list;

public:
    explicit LoanListModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    bool insert(lib::LoanItem item);
    bool remove(lib::LoanItem item);
    void loadFromDB(QVector<lib::LoanItem> items);

public slots:
    void whenItemUpdated(lib::LoanItem item);
    void whenIteminserted(lib::LoanItem item);
    void whenItemRemoved(lib::LoanItem item);
};

#endif // LOANLISTMODEL_H
