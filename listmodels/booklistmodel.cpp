#include "booklistmodel.h"
#include <QBrush>

BookListModel::BookListModel(QObject *parent) :
    QAbstractListModel(parent)
{
    // TODO
    // get existing entries from database
}

int BookListModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid()) {
        return 0; // prevent creating a tree model
    }

    return list.size();
}

QVariant BookListModel::data(const QModelIndex &index, int role) const
{
    // if index is not valid we do nothing.
    if(index.isValid()) {
        // get the requested Book from the vector
        lib::Book entry = list.at(index.row());

        switch (role) {
        case Qt::DisplayRole:
            // return the string to display in the list
            // QString is converted to QVariant by Qt
            return QString("%1 - %2, %3")
                    .arg(entry.getTitle()) // %1 title
                    .arg(entry.getAuthor()) // %2 author
                    .arg(entry.getISBN()); // %3 ISBN
            break;
        case Qt::UserRole: {
            if(entry.getLoaned() != 1) {
            // we want to return the object in the list, so we can use it elsewhere.
            // the Book object is not converted, so we pack it in a QVariant.
                QVariant qv;
                qv.setValue(entry);
                return qv;
                break;
            }
        }
        case Qt::BackgroundRole:
            if(entry.getLoaned() == 1) {
                return QBrush(Qt::red);
            }
            break;
        default: // we don't want to do anything here
            break;
        }
    }
    // return empty QVariant if we don't want to list anything
    return QVariant();
}


bool BookListModel::insert(lib::Book book)
{
    if(book.isValid()) {
        // notify that we begin inserting data
        beginInsertRows(QModelIndex(), list.size(), list.size());
        // insert in list
        list.append(book);

        // update database here

        // notify that inserting data has completed
        endInsertRows();
        return true;
    }
    return false;
}

bool BookListModel::remove(lib::Book book)
{
    if(list.contains(book)) {
        int row = list.indexOf(book);
        // notify that we begin removing data
        beginRemoveRows(QModelIndex(), row, row);
        list.remove(row);

        // update database here

        // notify that removing data has completed
        endRemoveRows();
        return true;
    }
    return false;
}

void BookListModel::loadFromDB(QVector<lib::Book> books)
{
    int l = books.size();
    beginInsertRows(QModelIndex(), 0, l - 1);
    list.swap(books);
    endInsertRows();
}

void BookListModel::whenItemUpdated(lib::Book book)
{
    // books are matched by ISBN
    if(book.isValid() && list.contains(book)) {
        int row = list.indexOf(book);
        list.replace(row, book);

        // update database here

        // notify that the data has changed

        emit dataChanged(index(row), index(row));
    }
}

void BookListModel::whenItemInserted(lib::Book book)
{
    // re-use insert function
    this->insert(book);
}

void BookListModel::whenItemRemoved(lib::Book book)
{
    // re-use remove function
    this->remove(book);
}
