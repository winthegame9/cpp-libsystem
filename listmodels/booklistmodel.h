#ifndef BOOKLISTMODEL_H
#define BOOKLISTMODEL_H

#include <QAbstractListModel>
#include <QVector>
#include "types/t_book.h"

class BookListModel : public QAbstractListModel
{
    Q_OBJECT

    QVector<lib::Book> list;


public:
    explicit BookListModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    bool insert(lib::Book book);
    bool remove(lib::Book book);
    void loadFromDB(QVector<lib::Book> books);

public slots:
    void whenItemUpdated(lib::Book book);
    void whenItemInserted(lib::Book book);
    void whenItemRemoved(lib::Book book);
};

#endif // BOOKLISTMODEL_H
