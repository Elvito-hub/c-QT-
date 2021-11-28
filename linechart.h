#ifndef LINECHART_H
#define LINECHART_H

#include <QWidget>
#include <QPainter>
#include<QDate>
#include"mydb.h"

namespace Ui {
class LineChart;
}

class LineChart : public QWidget
{
    Q_OBJECT

public:
    explicit LineChart(QWidget *parent = 0);
    QPainter *painter;
    void paintEvent(QPaintEvent *);
    float diff = 7;
    int jul1,jul2;
    ~LineChart();

private:
    Ui::LineChart *ui;
};

#endif // LINECHART_H
