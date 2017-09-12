#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "mainwindow.h"


namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    MainWindow w;
    bool checkPasswd();
    ~login();

private slots:
    void on_pushButton_clicked();

    void on_passwd_edit_returnPressed();

private:
    Ui::login *ui;
};

#endif // LOGIN_H
