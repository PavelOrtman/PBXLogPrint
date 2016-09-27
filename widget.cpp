#include "widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLay = new QVBoxLayout(this);

    QHBoxLayout *topLay = new QHBoxLayout;
    topLay->addWidget(new QLabel(QObject::trUtf8("Телефон:")));
    topLay->addWidget(lineEdit = new QLineEdit);
    topLay->addWidget(new QLabel(QObject::trUtf8("с:")));
    topLay->addWidget(fromDateEdit = new QDateEdit);
    topLay->addWidget(new QLabel(QObject::trUtf8("по:")));
    topLay->addWidget(toDateEdit = new QDateEdit);
    topLay->addWidget(goBtn = new QPushButton("Сформировать"));
    QObject::connect(goBtn, SIGNAL(clicked(bool)), this, SLOT(goSlot()));
    mainLay->addLayout(topLay);
    mainLay->addWidget(log = new QTextEdit);
    log->setReadOnly(true);
    log->setFont(QFont("Courier New", 8));

    fromDateEdit->setCalendarPopup(true);
    toDateEdit->setCalendarPopup(true);
    fromDateEdit->setDate(QDate::fromString("01" + QDate::currentDate().toString(".MM.yyyy"), "dd.MM.yyyy"));
    toDateEdit->setDate(QDate::currentDate());

    mainDB = QSqlDatabase::addDatabase("QSQLITE", "Main");
    mainDB.setDatabaseName("e:/Send/LinkageServer/smdr.db3");
    mainDB.open();
}
Widget::~Widget()
{
}

void Widget::goSlot()
{
    log->clear();
    log->append("Дата Время;Кто;Кому;Продолжительность");
    QSqlQuery query(mainDB);

    query.prepare("SELECT DAYTIME, FROMLINE, TOLINE, duration FROM log WHERE (DAYTIME >= :d1) AND "
                  "(DAYTIME < :d2) AND (FROMLINE = :t1 OR TOLINE = :t2) order by daytime");
    query.bindValue(":d1", fromDateEdit->date());
    query.bindValue(":d2", toDateEdit->date().addDays(1));
    query.bindValue(":t1", lineEdit->text());
    query.bindValue(":t2", lineEdit->text());
    if (!query.exec()) {
        log->append(query.lastError().text());
        return;
    }

    while (query.next()) {
        log->append(query.value(0).toDateTime().toLocalTime().toString("dd.MM.yyyy hh:mm:ss") + ";"
                    + query.value(1).toString() + ";" + query.value(2).toString() + ";"
                    + query.value(3).toTime().toString("hh:mm:ss"));
    }
}
