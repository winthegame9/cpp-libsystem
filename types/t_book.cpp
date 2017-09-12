#include "t_book.h"

lib::Book::Book()
{

}

lib::Book::Book(QString _isbn, QString _title, QString _author,
           QDate _published, short _loaned) :
    isbn(_isbn), title(_title), author(_author),
    published(_published), loaned(_loaned)
{
    // values assigned in initializer list
}

lib::Book::Book(const lib::Book &other)
{
    isbn = other.getISBN();
    title = other.getTitle();
    author = other.getAuthor();
    published = other.getPublished();
    loaned = other.getLoaned();
}

void lib::Book::setISBN(QString value)
{
    isbn = value;
}

void lib::Book::setTitle(QString value)
{
    title = value;
}

void lib::Book::setAuthor(QString value)
{
    author = value;
}

void lib::Book::setPublished(QDate value)
{
    published = value;
}

void lib::Book::setLoaned(short value)
{
    loaned = value;
}

QString lib::Book::getISBN() const
{
    return isbn;
}

QString lib::Book::getTitle() const
{
    return title;
}

QString lib::Book::getAuthor() const
{
    return author;
}

QDate lib::Book::getPublished() const
{
    return published;
}

QString lib::Book::getPublishedStr(QString format) const
{
    return published.toString(format);
}

short int lib::Book::getLoaned() const
{
    return loaned;
}

bool lib::Book::isValid() const
{
    bool valid = !isbn.isEmpty()
            && !author.isEmpty();
    return valid;
}

bool lib::Book::operator ==(const lib::Book &rhs) const
{
    return (isbn == rhs.getISBN());
}
