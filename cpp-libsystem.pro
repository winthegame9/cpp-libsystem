#-------------------------------------------------
#
# Project created by QtCreator 2017-05-13T15:34:56
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cpp-libsystem
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    dialogs/bookdialog.cpp \
    dialogs/persondialog.cpp \
    listmodels/booklistmodel.cpp \
    listmodels/loanlistmodel.cpp \
    listmodels/personlistmodel.cpp \
    registerwidget/bookregister.cpp \
    registerwidget/borrowerregister.cpp \
    registerwidget/librarianregister.cpp \
    registerwidget/loanregister.cpp \
    types/t_book.cpp \
    types/t_loanitem.cpp \
    types/t_person.cpp \
    dbmanager.cpp \
    loanregistration.cpp \
    login.cpp

HEADERS  += \
    dialogs/bookdialog.h \
    dialogs/persondialog.h \
    mainwindow.h \
    listmodels/booklistmodel.h \
    listmodels/loanlistmodel.h \
    listmodels/personlistmodel.h \
    registerwidget/bookregister.h \
    registerwidget/borrowerregister.h \
    registerwidget/librarianregister.h \
    registerwidget/loanregister.h \
    types/t_book.h \
    types/t_loanitem.h \
    types/t_person.h \
    dbmanager.h \
    loanregistration.h \
    login.h

FORMS    += \
    dialogs/bookdialog.ui \
    dialogs/persondialog.ui \
    registerwidget/bookregister.ui \
    registerwidget/borrowerregister.ui \
    registerwidget/librarianregister.ui \
    registerwidget/loanregister.ui \
    borrowerw.ui \
    librarian.ui \
    librarianw.ui \
    loanregistration.ui \
    login.ui \
    mainwindow.ui

RESOURCES += \
    resource.qrc
