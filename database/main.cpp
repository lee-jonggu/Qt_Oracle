#include "widget.h"

#include <QApplication>
#include <QTableView>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setDatabaseName(":memory:");
    db.setDatabaseName("./tempDB");
    if (!db.open()) return false;

    QSqlQuery q;
//    q.exec("create table if not exists person(id integer primary key,"\
//           "firstname varchar2(20) not null, lastname varchar2(20));");
//    q.exec("insert into person values(1,'yongsu','kang');");
//    q.exec("insert into person(firstname, lastname) values('Soomi','Kim')");
//    q.exec("insert into person(firstname, lastname) values('hanmi', 'Lee'),('YoungJin','Suh'),('YoungHwa','Ryu');");
    q.exec("delete from person where id = 1;");

    return true;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Widget w;
//    w.show();

    if (!createConnection()) return 1;

    QSqlTableModel qm;
//    qm.setQuery("select * from person");
//    qm.setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
//    qm.setHeaderData(1, Qt::Horizontal, QObject::tr("First Name"));
//    qm.setHeaderData(2, Qt::Horizontal, QObject::tr("Last Name"));
    qm.setTable("person");
//    qm.setEditStrategy(QSqlTableModel::OnManualSubmit);
    qm.select();

    QTableView *tableview = new QTableView;
    tableview->setModel(&qm);
    tableview->setWindowTitle(QObject::tr("Query Model"));
//    tableview->hideColumn(0);
    tableview->show();

    return a.exec();
}
