#ifndef DBMANAGER_H
#define DBMANAGER_H


#include <QtSql>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include <QString>
#include <QObject>
#include <QListWidgetItem>


class DBManager
{
    QString databaseName;
public:
    QSqlDatabase mydb;
    DBManager(QString databaseName);
    //These must be called when starting up
    void init_book_db();
    void init_loan_item_db();
    void init_person_db();
    //--------------------------------------
    void get_books();
    void close_connection();
    void connect_to_db();

    //Add functions
    void add_book(QString, QString, QString, QString, short);
    void add_loan_item(QString, QString, QString);
    void add_person(int, QString, QString, QString, QString, QString, QString);

    //Update functions
    void update_book(QString);
    void update_loan_item(QString, QString, int);

    //Delete functions
    void delete_book(QString);
};

#endif // DBMANAGER_H
