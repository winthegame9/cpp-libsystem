#include "mainwindow.h"
#include "login.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTimer>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/resource/img/splsh.png"));
    splash->show();

    QTimer::singleShot(2500,splash,SLOT(close()));

    login l;
    l.show();

    /*    //Give access to mainwindow
        MainWindow w;
        QTimer::singleShot(2500,splash,SLOT(close()));
        QTimer::singleShot(2500,&w,SLOT(show()));
*/


    return app.exec();
}
