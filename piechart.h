#ifndef PIECHART_H
#define PIECHART_H

#include <QWidget>
#include"mydb.h"

namespace Ui {
class PieChart;
}

class PieChart : public QWidget
{
    Q_OBJECT

public:
    explicit PieChart(QWidget *parent = 0);
    QPainter *painter;
    void paintEvent(QPaintEvent *);
    ~PieChart();

private:
    Ui::PieChart *ui;
};

#endif // PIECHART_H
