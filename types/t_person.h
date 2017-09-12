#ifndef T_PERSON_H
#define T_PERSON_H

#include <QMetaType>
#include <QString>
#include <QDate>

namespace lib {

    enum PersonRole {
        Borrower = 1,
        Librarian = 2
    };

    class Person
    {
        static long nextID;
        long personID;
        QString firstname;
        QString lastname;
        QString address;
        QDate registered;
        QDate deregistered;
        lib::PersonRole role;

    public:
        Person();
        Person(QString fn, QString ln, QString addr,
               QDate registered, lib::PersonRole role = lib::Borrower);
        Person(const Person &other);

        void setPersonID(long value);
        void setFirstname(QString value);
        void setLastname(QString value);
        void setAddress(QString value);
        void setRegistered(QDate value);
        void setDeregistered(QDate value);
        void setRole(lib::PersonRole value);

        long getPersonID() const;
        QString getFirstname() const;
        QString getLastname() const;
        QString getFullname() const; // get combo of first and last name
        QString getAddress() const;
        QDate getRegistered() const;
        QString getRegisteredStr(QString format = "dd.MM.yyyy") const;
        QDate getDeregistered() const;
        QString getDeregisteredStr(QString format = "dd.MM.yyyy") const;
        lib::PersonRole getRole() const;
        QString getRoleStr() const;

        bool isValid() const;
        bool operator ==(const lib::Person &rhs) const;
    };

}

Q_DECLARE_METATYPE(lib::Person)

#endif // T_PERSON_H
