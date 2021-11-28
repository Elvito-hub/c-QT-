#ifndef POLARCHART_H
#define POLARCHART_H

#include <QWidget>
#include<QPainter>
#include "mydb.h"
#include<QDate>


namespace Ui {
class PolarChart;
}

class PolarChart : public QWidget
{
    Q_OBJECT

public:
    explicit PolarChart(QWidget *parent = 0);
    QString thDate;
    void paintEvent(QPaintEvent *);
    ~PolarChart();

private:
    Ui::PolarChart *ui;
};

#endif // POLARCHART_H
