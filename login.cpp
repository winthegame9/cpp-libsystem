#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include <QSplashScreen>
#include <QTimer>


login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);

    this->setWindowTitle("Please login");

    //Request focus
    ui->username_edit->setFocusPolicy(Qt::StrongFocus);
    ui->username_edit->setFocus();

    QIcon icon(":/resource/img/login.png");
    this->setWindowIcon(icon);
    QWidget::setWindowIcon(icon);

    this->setFixedWidth(369);
    this->setFixedHeight(340);
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    this->setSizeGripEnabled(false);

}

bool login::checkPasswd()
{
    QString user_admin = "admin";
    QString paswd_admin = "hioa";
    if(ui->username_edit->text() == user_admin && ui->passwd_edit->text() == paswd_admin)
    {
        return true;
    }
    else
    {
        return false;
    }
    return false;
}

login::~login()
{
    delete ui;
}


void login::on_pushButton_clicked()
{
    if(checkPasswd())
    {
        //Simply close the window
        //Could've also called the DESTRUCTOR
        this->hide();
        //Give access to mainwindow
        QTimer::singleShot(2500,&w,SLOT(show()));
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Wrong password\n"
                       "Please try again");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Wrong Password");

        QIcon icon(":/resource/img/splsh.ico");
        QPixmap exportSuccess(":/resource/img/messagebox_critical.png");
        QPixmap newPixmap = exportSuccess.scaled(QSize(50,50),  Qt::KeepAspectRatio);
        msgBox.setWindowIcon(icon);
        msgBox.setIconPixmap(newPixmap);
        msgBox.exec();
    }
}

void login::on_passwd_edit_returnPressed()
{
    if(checkPasswd())
    {
        //Simply close the window
        //Could've also called the DESTRUCTOR
        this->hide();
        //Give access to mainwindow
        QTimer::singleShot(2500,&w,SLOT(show()));
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Wrong password\n"
                       "Please try again");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Wrong Password");

        QIcon icon(":/resource/img/splsh.ico");
        QPixmap exportSuccess(":/resource/img/messagebox_critical.png");
        QPixmap newPixmap = exportSuccess.scaled(QSize(50,50),  Qt::KeepAspectRatio);
        msgBox.setWindowIcon(icon);
        msgBox.setIconPixmap(newPixmap);
        msgBox.exec();
    }
}
