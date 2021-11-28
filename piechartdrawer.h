#ifndef PIECHARTDRAWER_H
#define PIECHARTDRAWER_H
#include<QWidget>
#include"mydb.h"


class PieChartDrawer: public QWidget
{
    Q_OBJECT
public:
    explicit PieChartDrawer(QWidget *parent = 0);
    ~PieChartDrawer();
protected:
    void paintEvent(QPaintEvent *);
};

#endif // PIECHARTDRAWER_H
