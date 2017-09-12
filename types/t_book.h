#ifndef LIBBOOK_H
#define LIBBOOK_H

#include <QMetaType>
#include <QString>
#include <QDate>

namespace lib {

    class Book
    {

        QString isbn;
        QString title;
        QString author;
        QDate published;
        short int loaned;

    public:
        Book();
        Book(QString _isbn, QString _title, QString _author,
             QDate _published, short int loaned = 0);
        Book(const lib::Book &other);

        void setISBN(QString value);
        void setTitle(QString value);
        void setAuthor(QString value);
        void setPublished(QDate value);
        void setLoaned(short int value);

        QString getISBN() const;
        QString getTitle() const;
        QString getAuthor() const;
        QDate getPublished() const;
        QString getPublishedStr(QString format = "dd.MM.yyyy") const;
        short int getLoaned() const;

        bool isValid() const;
        bool operator ==(const lib::Book &rhs) const;
    };

}

Q_DECLARE_METATYPE(lib::Book)

#endif // LIBBOOK_H
