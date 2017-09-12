#include "t_loanitem.h"

long int lib::LoanItem::nextID = 1;

lib::LoanItem::LoanItem()
{

}

lib::LoanItem::LoanItem(lib::Book _book,
                        lib::Person _borrower,
                        lib::Person _librarian) :
    book(_book),
    borrower(_borrower),
    librarian(_librarian)
{
    loanID = nextID;
    nextID++;
    outDate = QDate::currentDate();
    dueDate = outDate.addDays(7);
}

lib::LoanItem::LoanItem(const LoanItem &other)
{
    loanID = other.getLoanID();
    book = other.getBook();
    borrower = other.getBorrower();
    librarian = other.getLibrarian();
    outDate = other.getOutDate();
    dueDate = other.getDueDate();
    inDate = other.getInDate();
}

long int lib::LoanItem::getLoanID() const
{
    return loanID;
}

lib::Book lib::LoanItem::getBook() const
{
    return book;
}

lib::Person lib::LoanItem::getBorrower() const
{
    return borrower;
}

lib::Person lib::LoanItem::getLibrarian() const
{
    return librarian;
}

QDate lib::LoanItem::getOutDate() const
{
    return outDate;
}

QDate lib::LoanItem::getDueDate() const
{
    return dueDate;
}

QDate lib::LoanItem::getInDate() const
{
    return inDate;
}

void lib::LoanItem::setLoanID(long value)
{
    loanID = value;
    if(nextID <= value) {
        nextID = value + 1;
    }
}

void lib::LoanItem::setBook(lib::Book value)
{
    book = value;
}

void lib::LoanItem::setBorrower(lib::Person value)
{
    borrower = value;
}

void lib::LoanItem::setLibrarian(lib::Person value)
{
    librarian = value;
}

void lib::LoanItem::setOutDate(QDate value)
{
    outDate = value;
}

void lib::LoanItem::setDueDate(QDate value)
{
    dueDate = value;
}

void lib::LoanItem::setInDate(QDate value)
{
    inDate = value;
}

QString lib::LoanItem::getOutDateStr(QString format) const
{
    return outDate.toString(format);
}

QString lib::LoanItem::getDueDateStr(QString format) const
{
    return dueDate.toString(format);
}

QString lib::LoanItem::getInDateStr(QString format) const
{
    return inDate.toString(format);
}

bool lib::LoanItem::extendLoantime(int days)
{
    // can not reduce loan time
    // can only extend up to 14 days at a time
    if(days > 0 && days <= 14) {
        dueDate = dueDate.addDays(days);
        return true;
    }
    return false;
}

bool lib::LoanItem::returnBook()
{
    // check if book has already been returned
    if(!inDate.isValid()) {
        inDate = QDate::currentDate();
        return inDate.isValid();
    }
    return false;
}

lib::LoanStatus lib::LoanItem::status() const {
    if(inDate.isValid()) {
        // book has been returned
        if(inDate > dueDate)
            return lib::LateReturn;
        else
            return lib::Returned;
    } else {
        // book has not been returned
        QDate current = QDate::currentDate();
        if(current > dueDate)
            return lib::Overdue;
        else
            return lib::Active;
    }
}

QString lib::LoanItem::statusStr() const
{
    QString ret;
    lib::LoanStatus s = status();

    switch (s) {
    case lib::Active:
        ret = "active";
        break;
    case lib::Returned:
        ret = "returned";
        break;
    case lib::Overdue:
        ret = "overdue";
        break;
    case lib::LateReturn:
        ret = "returned late";
        break;
    default:
        break;
    }

    return ret;
}

bool lib::LoanItem::isValid() const
{
    bool valid = (loanID != 0)
            && book.isValid()
            && borrower.isValid()
            && librarian.isValid()
            && outDate.isValid()
            && dueDate.isValid();
    return valid;
}

bool lib::LoanItem::operator ==(const lib::LoanItem &rhs) const
{
    if(loanID != 0 && rhs.getLoanID() != 0) {
        return loanID == rhs.getLoanID();
    } else {
        bool eq = book == rhs.getBook()
                && borrower == rhs.getBorrower()
                && librarian == rhs.getLibrarian()
                && outDate == rhs.getOutDate();
        return eq;
    }
}
