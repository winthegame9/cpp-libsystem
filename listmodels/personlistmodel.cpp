#include "personlistmodel.h"
#include <QBrush>

PersonListModel::PersonListModel(int personRole, QObject *parent) :
    QAbstractListModel(parent)
{
    switch (personRole) {
    case lib::Borrower:
        roleSelector = "borrower";
        break;
    case lib::Librarian:
        roleSelector = "librarian";
        break;
    default:
        break;
    }
}

int PersonListModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid()) {
        return 0;
    }

    return list.size();
}

QVariant PersonListModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid()) {
        lib::Person entry = list.at(index.row());

        switch (role) {
        case Qt::DisplayRole:
            return QString("%1 - %2, %3 : %4")
                    .arg(QString::number(entry.getPersonID()))   // %1 ID
                    .arg(entry.getLastname())   // %2 lastname
                    .arg(entry.getFirstname()) // %3 firstname
                    .arg(entry.getRoleStr()); // %4 role string
            break;
        case Qt::UserRole: {
            QVariant qv;
            qv.setValue(entry);
            return qv;
            break;
        }
        case Qt::ForegroundRole:
            if(entry.getDeregistered().isValid()) {
                return QBrush(Qt::gray);
            }
            break;
        default:
            break;
        }
    }

    return QVariant();
}

bool PersonListModel::insert(lib::Person person)
{
    if(person.isValid()) {
        beginInsertRows(QModelIndex(), list.size(), list.size());
        list.append(person);
        endInsertRows();
        return true;
    }
    return false;
}

bool PersonListModel::remove(lib::Person person)
{
    if(list.contains(person)) {
        int row = list.indexOf(person);
        beginRemoveRows(QModelIndex(), row, row);
        list.remove(row);
        endRemoveRows();
        return true;
    }
    return false;
}

void PersonListModel::loadFromDB(QVector<lib::Person> items)
{
    int l = items.size();
    beginInsertRows(QModelIndex(), 0, l - 1);
    list.swap(items);
    endInsertRows();
}

void PersonListModel::whenItemUpdated(lib::Person person)
{
    if(person.isValid() && list.contains(person)) {
        int row = list.indexOf(person);
        list.replace(row, person);
        emit dataChanged(index(row), index(row));
    }
}

void PersonListModel::whenItemInserted(lib::Person person)
{
    this->insert(person);
}

void PersonListModel::whenItemRemoved(lib::Person person)
{
    this->remove(person);
}
