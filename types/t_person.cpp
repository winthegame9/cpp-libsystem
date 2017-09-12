#include "t_person.h"

long lib::Person::nextID = 1;

lib::Person::Person()
{

}

lib::Person::Person(QString fn, QString ln, QString addr, QDate reg, lib::PersonRole _role) :
    firstname(fn), lastname(ln), address(addr), registered(reg), role(_role)
{
    personID = nextID;
    nextID++;
}

lib::Person::Person(const Person &other)
{
    personID = other.getPersonID();
    firstname = other.getFirstname();
    lastname = other.getLastname();
    address = other.getAddress();
    registered = other.getRegistered();
    deregistered = other.getDeregistered();
    role = other.getRole();
}

void lib::Person::setPersonID(long value)
{
    personID = value;
    if(nextID <= value) {
        nextID = value + 1;
    }
}

void lib::Person::setFirstname(QString value)
{
    firstname = value;
}

void lib::Person::setLastname(QString value)
{
    lastname = value;
}

void lib::Person::setAddress(QString value)
{
    address = value;
}

void lib::Person::setRegistered(QDate value)
{
    registered = value;
}

void lib::Person::setDeregistered(QDate value)
{
    deregistered = value;
}

void lib::Person::setRole(lib::PersonRole value)
{
    role = value;
}

long lib::Person::getPersonID() const
{
    return personID;
}

QString lib::Person::getFirstname() const
{
    return firstname;
}

QString lib::Person::getLastname() const
{
    return lastname;
}

QString lib::Person::getFullname() const
{
    return firstname + " " + lastname;
}

QString lib::Person::getAddress() const
{
    return address;
}

QDate lib::Person::getRegistered() const
{
    return registered;
}

QString lib::Person::getRegisteredStr(QString format) const
{
    return registered.toString(format);
}

QDate lib::Person::getDeregistered() const
{
    return deregistered;
}

QString lib::Person::getDeregisteredStr(QString format) const
{
    return deregistered.toString(format);
}

lib::PersonRole lib::Person::getRole() const
{
    return role;
}

QString lib::Person::getRoleStr() const
{
    if(role == lib::Librarian)
        return "librarian";
    return "borrower";
}

bool lib::Person::isValid() const
{
    bool valid = !firstname.isEmpty()
            && !lastname.isEmpty()
            && !address.isEmpty()
            && registered.isValid();
    return valid;
}

bool lib::Person::operator ==(const lib::Person &rhs) const
{
    if(personID != 0 && rhs.getPersonID() != 0) {
        return personID == rhs.getPersonID();
    } else {
        bool eq = firstname == rhs.getFirstname()
                && lastname == rhs.getLastname()
                && address == rhs.getAddress();
        return eq;
    }
}
