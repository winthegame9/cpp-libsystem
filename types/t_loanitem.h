#ifndef LOANITEM_H
#define LOANITEM_H

#include <QMetaType>
#include <QString>
#include <QDate>
#include "types/t_book.h"
#include "types/t_person.h"

namespace lib {

    enum LoanStatus {
        Returned = 1,
        Active = 2,
        Overdue = -1,
        LateReturn = -2
    };

    class LoanItem
    {
        static long int nextID;
        long int loanID;
        lib::Book book;
        lib::Person borrower;
        lib::Person librarian;
        QDate outDate;
        QDate dueDate;
        QDate inDate;

    public:
        LoanItem();
        LoanItem(lib::Book _book,
                 lib::Person _borrower,
                 lib::Person _librarian);
        LoanItem(const LoanItem &other);

        long int getLoanID() const;
        lib::Book getBook() const;
        lib::Person getBorrower() const;
        lib::Person getLibrarian() const;

        QDate getOutDate() const;
        QDate getDueDate() const;
        QDate getInDate() const;

        void setLoanID(long int value);
        void setBook(lib::Book value);
        void setBorrower(lib::Person value);
        void setLibrarian(lib::Person value);
        void setOutDate(QDate value);
        void setDueDate(QDate value);
        void setInDate(QDate value);

        QString getOutDateStr(QString format = "dd.MM.yyyy") const;
        QString getDueDateStr(QString format = "dd.MM.yyyy") const;
        QString getInDateStr(QString format = "dd.MM.yyyy") const;

        bool extendLoantime(int days = 7);
        bool returnBook();
        lib::LoanStatus status() const;
        QString statusStr() const;

        bool isValid() const;
        bool operator ==(const lib::LoanItem &rhs) const;
    };

}

Q_DECLARE_METATYPE(lib::LoanItem)

#endif // LOANITEM_H
