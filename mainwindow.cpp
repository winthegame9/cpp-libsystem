#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDate>
#include <QIcon>
#include <QPixmap>
#include <QPalette>
#include "types/t_book.h"
#include "types/t_person.h"
#include "dbmanager.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Set the window icon
    QIcon icon(":/resource/img/splsh.ico");
    this->setWindowIcon(icon);
    QWidget::setWindowIcon(icon);

    /*
    QPalette palette;
    palette.setColor(QPalette::Button, menuBar()->palette().color(QPalette::Window));
    ui->menuBar->setPalette(palette);
    */
    initWidgets();

    dbm.init_book_db();
    dbm.init_loan_item_db();
    dbm.init_person_db();

    // connect signals related to database operations
    // books
    connect(bookRegister, &BookRegister::itemInsert,
            this, &MainWindow::db_insert_book);
    connect(bookRegister, &BookRegister::itemUpdate,
            this, &MainWindow::db_update_book);
    connect(bookRegister, &BookRegister::itemRemove,
            this, &MainWindow::db_remove_book);

    // loanitems
    connect(ui->loanRegister, &LoanRegister::itemInsert,
            this, &MainWindow::db_insert_loanItem);
    connect(ui->loanRegister, &LoanRegister::itemUpdate,
            this, &MainWindow::db_update_loanItem);

    // librarians/borrowers
    connect(ui->librarianRegister, &LibrarianRegister::itemInsert,
            this, &MainWindow::db_insert_person);
    /*connect(ui->librarianRegister, &LibrarianRegister::itemUpdate,
            this, &MainWindow::db_update_person);*/
    connect(ui->borrowerRegister, &BorrowerRegister::itemInsert,
            this, &MainWindow::db_insert_person);
    /*connect(ui->borrowerRegister, &BorrowerRegister::itemUpdate,
            this, &MainWindow::db_update_person);*/

    lib::Book b1("12345125", "A title", "Jon", QDate::currentDate().addYears(-5));

    // test adding b1 to db
//    db_insert_book(b1);

    lib::Book b2("38558329", "The Second", "Alf", QDate::currentDate().addYears(-14));
    lib::Book b3("12253255", "Travelling time", "Bob", QDate::currentDate().addYears(-1));

    bookRegister->whenBookInsertFromMain(b1);
    bookRegister->whenBookInsertFromMain(b2);
    bookRegister->whenBookInsertFromMain(b3);

    lib::Person pb1("Albert", "Lans", "Street 1", QDate::currentDate().addMonths(-6), lib::Borrower);
    lib::Person pb2("Bobby", "Kansas", "Street 4", QDate::currentDate().addMonths(-3), lib::Borrower);
    lib::Person pb3("Romhilde", "Aans", "Street 2", QDate::currentDate().addMonths(-1), lib::Borrower);

    ui->borrowerRegister->whenPersonInsertedFromMain(pb1);
    ui->borrowerRegister->whenPersonInsertedFromMain(pb2);
    ui->borrowerRegister->whenPersonInsertedFromMain(pb3);

    lib::Person pl1("Hilde", "Graut", "Norw1", QDate::currentDate().addYears(-4), lib::Librarian);
    lib::Person pl2("Arne", "Pough", "Norw2", QDate::currentDate().addYears(-2), lib::Librarian);
    lib::Person pl3("Kari", "Traa", "Norw3", QDate::currentDate().addDays(-4), lib::Librarian);

    ui->librarianRegister->whenPersonInsertedFromMain(pl1);
    ui->librarianRegister->whenPersonInsertedFromMain(pl2);
    ui->librarianRegister->whenPersonInsertedFromMain(pl3);

    /// connect signals
    connect(bookRegister, &BookRegister::itemSelectionChanged,
            ui->loanRegistration, &LoanRegistration::whenCurrentBookChanged);
    connect(ui->borrowerRegister, &BorrowerRegister::itemSelectionChanged,
            ui->loanRegistration, &LoanRegistration::whenCurrentBorrowerChanged);
    connect(ui->librarianRegister, &LibrarianRegister::itemSelectionChanged,
            ui->loanRegistration, &LoanRegistration::whenCurrentLibrarianChanged);

    connect(ui->loanRegistration, &LoanRegistration::newLoanRegistered,
            ui->loanRegister, &LoanRegister::whenLoanRegistered);
    connect(ui->loanRegister, &LoanRegister::bookStatusChanged,
            bookRegister, &BookRegister::whenBookStatusUpdated);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::initWidgets()
{
    bookRegister = new BookRegister(this);
    ui->dockBooksWidget->setWidget(bookRegister);
}

/// private slots
void MainWindow::on_actionShow_Librarians_triggered(bool checked)
{
    // when checked == false hide librarianWidget
    // else show librarianWidget
    //librarianRegister->setVisible(checked);
    ui->dockLibrarianWidget->setVisible(checked);
}

void MainWindow::on_actionBook_list_triggered(bool checked)
{
    // when checked == false hide bookRegisterWidget
    // else show bookRegisterWidget
    ui->dockBooksWidget->setVisible(checked);
}

void MainWindow::on_actionLoan_register_triggered(bool checked)
{
    // when checked == false hide loanRegisterWidget
    // else show loanRegisterWidget    
    ui->loanRegister->setVisible(checked);
}

void MainWindow::on_actionShow_Borrowers_triggered(bool checked)
{
    // when checked == false hide dockwidget with borrowerRegister
    // else show borrowersWidget
    ui->dockBorrowersWidget->setVisible(checked);
}

void MainWindow::on_action_Exit_triggered()
{
    //Quits
    QCoreApplication::quit();
}

void MainWindow::db_insert_book(lib::Book book)
{
    qDebug("inserting book in database");
    dbm.add_book(book.getISBN(), book.getTitle(), book.getAuthor(), book.getPublishedStr("dd.MM.yyyy"), book.getLoaned());
}


void MainWindow::db_update_book(lib::Book book)
{
    qDebug("updating book in database");
    dbm.update_book(book.getISBN());
}

void MainWindow::db_remove_book(lib::Book book)
{
    qDebug("removing book from database");
    dbm.delete_book(book.getISBN());
}

void MainWindow::db_insert_loanItem(lib::LoanItem item)
{
    qDebug("inserting loanItem in database");
    dbm.add_loan_item(item.getOutDateStr("dd.MM.yyyy"),
                      item.getInDateStr("dd.MM.yyyy"),
                      item.getDueDateStr("dd.MM.yyyy"));
}

void MainWindow::db_update_loanItem(lib::LoanItem item)
{
    qDebug("updating loanItem in database");
    dbm.update_loan_item(item.getInDateStr("dd.MM.yyyy"),
                         item.getDueDateStr("dd.MM.yyyy"),
                         item.getLoanID());
}

void MainWindow::db_insert_person(lib::Person person)
{
    qDebug("inserting person in database");
    dbm.add_person(person.getPersonID(),
                    person.getFirstname(), person.getLastname(),
                    person.getAddress(), person.getRegisteredStr("dd.MM.yyyy"),
                    person.getDeregisteredStr("dd.MM.yyyy"),
                    person.getRoleStr());
}


void MainWindow::on_action_About_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("Library Managment System v1.1\n"
                   "All rights reserved HiOA 2017");
    msgBox.setIcon(QMessageBox::NoIcon);
    msgBox.setWindowTitle("About");

    QIcon icon(":/resource/img/splsh.ico");
    QPixmap exportSuccess(":/resource/img/splsh.ico");
    msgBox.setWindowIcon(icon);
    msgBox.setIconPixmap(exportSuccess);
    msgBox.exec();
}
