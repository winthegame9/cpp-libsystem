#ifndef BOOKDIALOG_H
#define BOOKDIALOG_H

#include <QDialog>
#include "types/t_book.h"

namespace Ui {
class BookDialog;
}

class BookDialog : public QDialog
{
    Q_OBJECT

    void setSaveButtonEnabled(bool enabled);

public:
    explicit BookDialog(QWidget *parent = 0);
    ~BookDialog();

signals:
    void bookCreated(lib::Book book);

private slots:
    void on_buttonBox_accepted();
    void checkLineEdits();

private:
    Ui::BookDialog *ui;
};

#endif // BOOKDIALOG_H
