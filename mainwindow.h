#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "types/t_book.h"
#include "types/t_loanitem.h"
#include "types/t_person.h"
#include "registerwidget/bookregister.h"
#include "dbmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    BookRegister *bookRegister;

    void initWidgets();
    DBManager dbm = DBManager("library.db");

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_actionShow_Librarians_triggered(bool checked);

    void on_actionBook_list_triggered(bool checked);

    void on_actionLoan_register_triggered(bool checked);

    void on_actionShow_Borrowers_triggered(bool checked);

    void on_action_Exit_triggered();

    void db_insert_book(lib::Book book);
    void db_update_book(lib::Book book);
    void db_remove_book(lib::Book book);

    void db_insert_loanItem(lib::LoanItem item);
    void db_update_loanItem(lib::LoanItem item);

    void db_insert_person(lib::Person person);

    void on_action_About_triggered();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
