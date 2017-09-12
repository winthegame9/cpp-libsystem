#ifndef BOOKREGISTER_H
#define BOOKREGISTER_H

#include <QWidget>
#include "listmodels/booklistmodel.h"
#include "types/t_book.h"

namespace Ui {
class BookRegister;
}

class BookRegister : public QWidget
{
    Q_OBJECT

    BookListModel *listModel;
    lib::Book current;

public:
    explicit BookRegister(QWidget *parent = 0);
    ~BookRegister();

    lib::Book getCurrent() const;
    void loadFromDB(QVector<lib::Book> books);

signals:
    void itemSelectionChanged(lib::Book book);
    void itemInsert(lib::Book book);
    void itemUpdate(lib::Book book);
    void itemRemove(lib::Book book);

private slots:
    void on_listView_clicked(const QModelIndex &index);

    void on_buttonCreate_clicked();

    void on_buttonRemove_clicked();

    void whenBookCreated(lib::Book book);

public slots:
    void whenBookStatusUpdated(lib::Book book);
    void whenBookInsertFromMain(lib::Book book);

private:
    Ui::BookRegister *ui;
};

#endif // BOOKREGISTER_H
