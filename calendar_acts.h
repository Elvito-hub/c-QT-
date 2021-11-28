#ifndef CALENDAR_ACTS_H
#define CALENDAR_ACTS_H

#include <QWidget>
#include <QCalendarWidget>
#include<QDialog>
#include<QTableView>
#include "mydb.h"
#include "polarchart.h"
#include"delegate.h"

namespace Ui {
class Calendar_Acts;
}

class Calendar_Acts : public QWidget
{
    Q_OBJECT

public:
    explicit Calendar_Acts(QWidget *parent = 0);
    QCalendarWidget *calendar;
    QTableView *table;
    PolarChart *ptrPolarchart;
    void updateTable(QString sdate);
    void updateStatusJudge(const QString name,const QString date);
    ~Calendar_Acts();

private slots:
    void on_pushButton_clicked();

    void onChoseDay(const QDate &date);

private:
    Ui::Calendar_Acts *ui;
};

#endif // CALENDAR_ACTS_H
