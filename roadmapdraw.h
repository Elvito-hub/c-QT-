#ifndef ROADMAPDRAW_H
#define ROADMAPDRAW_H

#include <QWidget>
#include<QDialog>
#include<QPainter>
#include<QPushButton>
#include<bits/stdc++.h>
#include"mydbrm.h"

namespace Ui {
class RoadmapDraw;
}

class RoadmapDraw : public QDialog
{
    Q_OBJECT

public:
    explicit RoadmapDraw(QWidget *parent = 0);
    QString title;
    QPainter *painter;
    QPushButton *nextStep;
    int totStep;
    int step;
    void Show();
    void paintEvent(QPaintEvent *);
    ~RoadmapDraw();

private:
    Ui::RoadmapDraw *ui;
private slots:
    void updateStep();
};

#endif // ROADMAPDRAW_H
