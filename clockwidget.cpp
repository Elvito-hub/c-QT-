#include "clockwidget.h"

#include<QPainter>
#include<QTime>
#include<QTimer>

ClockWidget::ClockWidget(QWidget *parent)
    : QWidget(parent)
{
    //create QTimer object
    QTimer *timer = new QTimer(this);

    //connect timer obj with our analog clock
    //QTimer::timeout() is emitted when timer timesout(/1s)
    //QOverload resolves function overloads
    connect(timer,&QTimer::timeout,this,QOverload<>::of(&ClockWidget::update));
    timer->start(500);
    resize(200,200);
}

void ClockWidget::paintEvent(QPaintEvent *)
{
    static const QPoint hourHand[7] = {
        QPoint(4, 8),
        QPoint(-4, 8),
        QPoint(-4, -40),
        QPoint(-6,-40),
        QPoint(0,-50),
        QPoint(6,-40),
        QPoint(4,-40)
    };
    static const QPoint minuteHand[7] = {
        QPoint(3, 8),
        QPoint(-3, 8),
        QPoint(-3,-60),
        QPoint(-5,-60),
        QPoint(0,-70),
        QPoint(5,-60),
        QPoint(3,-60)
    };
    static const QPoint secondHand[7] = {
        QPoint(2,8),
        QPoint(-2,8),
        QPoint(-2,-75),
        QPoint(-4,-75),
        QPoint(0,-85),
        QPoint(4,-75),
        QPoint(2,-75)
    };
    QColor hourColor(127,0,127);
    QColor minuteColor(0,127,127,191);
    QColor secondColor(150, 75, 0);

    int side= qMin(width(), height());
    QTime time = QTime::currentTime();

    QPainter painter(this);

    //Antialiasing makes edges smooth, helps colors to blend naturally
    painter.setRenderHint(QPainter::Antialiasing);
    //translate the coordinates system to given points
    painter.translate(width()/2,height()/2);

    painter.scale(side/200.0,side/200.0);

    painter.setPen(Qt::NoPen);
    //set brush to color
    painter.setBrush(hourColor);
    //aves the current painter state (pushes the state onto a stack)
    painter.save();
    //rotate to our hour loc 30deg*(hour+minute/60);
    painter.rotate(30.0*(time.hour()+time.minute()/60.0));
    //draw our hourPoints
    painter.drawConvexPolygon(hourHand,7);
    //restore saved painter state
    painter.restore();

    painter.setPen(hourColor);
    for(int i=1;i<=12;i++)
    {
        painter.drawLine(88,0,96,0);
        painter.rotate(30.0);
    }

    painter.setPen(Qt::NoPen);
    painter.setBrush(minuteColor);

    painter.save();

    //rotate to min loc 6deg*(minute+second/60)
    painter.rotate(6.0*(time.minute()+time.second()/60.0));

    //draw our minute points

    painter.drawConvexPolygon(minuteHand,7);
    painter.restore();

    painter.setPen(minuteColor);

    for(int j=0;j<60;j++)
    {
        if(j%5!=0)
            painter.drawLine(92,0,96,0);
        painter.rotate(6.0);
    }

    painter.setPen(Qt::NoPen);
    painter.setBrush(secondColor);

    painter.save();

    //rotate to min loc 6deg*(minute+second/60)
    painter.rotate(360.0*(time.second()/60.0));
    painter.drawConvexPolygon(secondHand,7);
    painter.restore();

    painter.setPen(Qt::black);
    painter.drawLine(-100,-100,-100,100);
    painter.drawLine(-100,100,100,100);
    painter.drawLine(100,100,100,-100);
    painter.drawLine(100,-100,-100,-100);

}
