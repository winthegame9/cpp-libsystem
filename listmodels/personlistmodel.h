#ifndef PERSONLISTMODEL_H
#define PERSONLISTMODEL_H

#include <QAbstractListModel>
#include <QVector>
#include "types/t_person.h"

class PersonListModel : public QAbstractListModel
{
    Q_OBJECT

    QVector<lib::Person> list;
    QString roleSelector;

public:
    explicit PersonListModel(int personRole = lib::Borrower, QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    bool insert(lib::Person person);
    bool remove(lib::Person person);
    void loadFromDB(QVector<lib::Person> items);

public slots:
    void whenItemUpdated(lib::Person person);
    void whenItemInserted(lib::Person person);
    void whenItemRemoved(lib::Person person);

};

#endif // PERSONLISTMODEL_H
