#include "loanlistmodel.h"
#include <QBrush>

LoanListModel::LoanListModel(QObject *parent) :
    QAbstractListModel(parent)
{

}

int LoanListModel::rowCount(const QModelIndex &parent) const
{
    if(parent.isValid()) {
        return 0;
    }

    return list.size();
}

QVariant LoanListModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid()) {
        lib::LoanItem entry = list.at(index.row());

        switch (role) {
        case Qt::DisplayRole:
            return QString("%1, %2, %3: %4 - %5 [%6]")
                    .arg(entry.getLoanID())
                    .arg(entry.getBorrower().getLastname())
                    .arg(entry.getBook().getTitle())
                    .arg(entry.getOutDateStr())
                    .arg(entry.getDueDateStr())
                    .arg(entry.statusStr());
            break;
        case Qt::UserRole: {
            QVariant qv;
            qv.setValue(entry);
            return qv;
            break;
        }
        case Qt::BackgroundRole:
            if(entry.status() == lib::Returned) {
                // green background
                return QBrush(Qt::green);
            } else if(entry.status() == lib::LateReturn) {
                // greenish / patterned
                return QBrush(QColor(100, 190, 130), Qt::BDiagPattern);
            } else if(entry.status() == lib::Overdue) {
                // red background
                return QBrush(Qt::red);
            }
            break;
        default:
            break;
        }
    }

    return QVariant();
}

bool LoanListModel::insert(lib::LoanItem item)
{
    if(item.isValid() && !list.contains(item)) {
        beginInsertRows(QModelIndex(), list.size(), list.size());
        list.append(item);
        // update db
        endInsertRows();
        return true;
    }
    return false;
}

bool LoanListModel::remove(lib::LoanItem item)
{
    if(list.contains(item)) {
        int row = list.indexOf(item);
        beginRemoveRows(QModelIndex(), row, row);
        list.remove(row);
        // update db
        endRemoveRows();
        return true;
    }
    return false;
}

void LoanListModel::loadFromDB(QVector<lib::LoanItem> items)
{
    int l = items.size();
    beginInsertRows(QModelIndex(), 0, l);
    list.swap(items);
    endInsertRows();
}

void LoanListModel::whenItemUpdated(lib::LoanItem item)
{
    if(item.isValid() && list.contains(item)) {
        int row = list.indexOf(item);
        list.replace(row, item);
        emit dataChanged(index(row), index(row));
    }
}

void LoanListModel::whenIteminserted(lib::LoanItem item)
{
    this->insert(item);
}

void LoanListModel::whenItemRemoved(lib::LoanItem item)
{
    this->remove(item);
}
