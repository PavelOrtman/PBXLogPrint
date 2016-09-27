#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QBoxLayout>
#include <QtSql>
#include <QDateEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

class Widget : public QWidget
{
    Q_OBJECT

    QSqlDatabase                mainDB;
    QTextEdit                   *log;
    QDateEdit                   *fromDateEdit;
    QDateEdit                   *toDateEdit;

    QPushButton                 *goBtn;
    QLineEdit                   *lineEdit;

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void                        goSlot();
};

#endif // WIDGET_H
