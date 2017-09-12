#include "dbmanager.h"
#include <QListWidgetItem>
#include <QDialog>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QVector>
#include <string>
#include <QSqlQueryModel>
#include <QModelIndex>

/*                                  *
    This file contains all
    the neccessary database calls
    for creating, updating and removing
    our tables
*                                   */

DBManager::DBManager(QString databaseName)
{
    this->databaseName = databaseName;
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    //ONLY WORKS IF THE DB IS ON THE HARD DRIVE FOR THE MOMENT
    mydb.setDatabaseName(this->databaseName);

    mydb.open();
    connect_to_db();
}

/*''''''''''''''''''''''''''''''''''''''''''''''''
 * these functions are for
 * managing the db connection
 * '''''''''''''''''''''''''''''''''''''''''''''''
*/

//close connection
void DBManager::close_connection(){
    mydb.close();
    mydb.removeDatabase(QSqlDatabase::defaultConnection);
}

//connect to db
void DBManager::connect_to_db(){
    bool ok = mydb.isOpen();
    if(!ok)
    {
        mydb = QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName(this->databaseName);
        mydb.open();
        qDebug() << "Not connected to db.. error..";
        return;
    }
    else
    {
        qDebug() << "Successfully connected to db";
    }
}


//create book table
void DBManager::init_book_db(){
//    QString sql = "CREATE TABLE IF NOT EXISTS book (id PRIMARY KEY AUTOINCREMENT, isbn TEXT, title TEXT, author TEXT, published TEXT, loaned INTEGER)";
    QSqlQuery qry;
    qry.prepare("CREATE TABLE IF NOT EXISTS book"
                     "(id INTEGER PRIMARY KEY AUTOINCREMENT,"
                     "isbn TEXT,"
                     "title TEXT,"
                     "author TEXT,"
                     "published TEXT,"
                     "loaned INTEGER)");
    if( qry.exec() )
    {
        qDebug() << "Table created";
    }
    else
    {
        qDebug() << qry.lastError();
    }
    return;
}


//create loan item table
void DBManager::init_loan_item_db(){
    QSqlQuery qry;
    qry.prepare("CREATE TABLE loanitem"
                     "(id INTEGER PRIMARY KEY AUTOINCREMENT,"
                     "outDate TEXT,"
                     "dueDate TEXT,"
                     "inDate TEXT)");
    if( qry.exec() )
    {
        qDebug() << "Table created";
    }
    else
    {
        qDebug() << qry.lastError();
    }
}


//create person table
void DBManager::init_person_db(){
    QSqlQuery qry;
    qry.prepare("CREATE TABLE person"
                     "(id INTEGER PRIMARY KEY AUTOINCREMENT,"
                     "personID INTEGER,"
                     "firstname TEXT,"
                     "lastname TEXT,"
                     "address TEXT,"
                     "registered TEXT,"
                     "deregistered TEXT,"
                     "role TEXT)");
    if( qry.exec() )
    {
        qDebug() << "Table created";
    }
    else
    {
        qDebug() << qry.lastError();
    }
}

/*''''''''''''''''''''''''''''''''''''''''''''''''
 * calls to these functions are made
 * from the gui
 * '''''''''''''''''''''''''''''''''''''''''''''''
*/

//add book
void DBManager::add_book(QString isbn, QString title, QString author,
                         QString published, short status)
{
    QSqlQuery query;
    query.prepare("INSERT INTO book(isbn,title,author,published,loaned) "
    "VALUES(:isbn,:title,:author,:published,:loaned)");
    query.bindValue(":isbn", isbn);
    query.bindValue(":title", title);
    query.bindValue(":author", author);
    query.bindValue(":published", published);
    query.bindValue(":loaned", status);
    query.exec();
    if( query.exec() )
    {
        qDebug() << "Table created";
    }
    else
    {
        qDebug() << query.lastError();
    }
}


//update book
void DBManager::update_book(QString isbn){
    QSqlQuery query;
    query.prepare("UPDATE book SET loaned = 1 where isbn = (:isbn)");
    query.bindValue(":isbn", isbn);
    query.exec();
    if( query.exec() )
    {
        qDebug() << "Book updated";
    }
    else
    {
        qDebug() << query.lastError();
    }
}

//update loan item
void DBManager::update_loan_item(QString inDate, QString dueDate, int loanID){
    QSqlQuery query;
    query.prepare("UPDATE loanitem SET inDate = (:inDate), dueDate = (:dueDate) where id = (:loanId)");
    query.bindValue(":inDate", inDate);
    query.bindValue(":dueDate", dueDate);
    query.bindValue(":loanID",loanID);
    query.exec();
    if( query.exec() )
    {
        qDebug() << "Loan item updated";
    }
    else
    {
        qDebug() << query.lastError();
    }
}

//add loan item
void DBManager::add_loan_item(QString outDate, QString inDate, QString dueDate){
    QSqlQuery query;
    query.prepare("INSERT INTO loanitem(outDate,dueDate,inDate) "
    "VALUES(:outDate,:dueDate,:inDate)");
    query.bindValue(":out", outDate);
    query.bindValue(":due", dueDate);
    query.bindValue(":in", inDate);
    query.exec();
    if( !query.exec() )
    {
        query.lastError();
    }
    else
    {
        qDebug() << "Loan item added";
    }
}


//add person
void DBManager::add_person(int personID, QString firstname, QString lastname,
                           QString address, QString registered, QString deregistered,
                           QString role){
    QSqlQuery query;
    query.prepare("INSERT INTO person(personID, firstname, lastname, address, registered, deregistered, role) "
    "VALUES(:pid,:fname,:lname,:add,:reg,:dereg,:role)");
    query.bindValue(":personID", personID);
    query.bindValue(":firstname", firstname);
    query.bindValue(":lastname", lastname);
    query.bindValue(":address", address);
    query.bindValue(":registered", registered);
    query.bindValue(":deregistered", deregistered);
    query.bindValue(":role", role);
    query.exec();
    if( !query.exec() )
    {
        query.lastError();
    }
    else
    {
        qDebug() << "Loan item added";
    }
}

//delete book
void DBManager::delete_book(QString isbn){
    QSqlQuery query;
    query.prepare("DELETE FROM book WHERE isbn = (:isbn) ");
    query.bindValue(":isbn", isbn);
    query.exec();
    if(!query.exec())
    {
        qDebug() << "removeBook error: "
        << query.lastError();
    }else
    {
        qDebug() << "Successful remove";
    }
}
