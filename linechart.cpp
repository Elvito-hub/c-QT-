#include "linechart.h"
#include "ui_linechart.h"
#include<QPainter>
#include<iostream>
#include <vector>
#include <utility>

LineChart::LineChart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LineChart)
{
    ui->setupUi(this);
    resize(1500,1000);
}

void LineChart::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::black);
    int h=900;
    for(int i=0;i<=10;i++)
    {
        painter.drawLine(300,h,1700,h);
        QString pt = QString::number(i);
        QRectF rect(280, h-10, 50,50);
        painter.drawText(rect,pt);
        h-=50;
    }

    float w = 300;
    float xdiff = 1400/diff;
    int k=jul1;
    for(int i=0;i<=diff;i++,k++)
    {
        QDate date1 = QDate::fromJulianDay(k);
        QString d = date1.toString("yyyy-MM-dd");
        QString xaxis = d.mid(5,5);
        QRectF rect1(w, 920, 50,50);
        //painter.rotate(30);
        painter.drawText(rect1,xaxis);
        //painter.rotate(-30);
        painter.drawLine(w,400,w,900);
        w+=xdiff;
    }
    std::vector<std::pair<int,int>> points;
    float x=300;
//   for(int i=jul1;i<=jul2;i++)
//    {

//        QDate date1 = QDate::fromJulianDay(i);
//        QString d = date1.toString("yyyy-MM-dd");
//        //daily average
//        QSqlQueryModel *model = new QSqlQueryModel(this);
//        QSqlQuery query(MyDB::getInstance1()->getDBInstance1());
//        query.prepare("select Name,StatusJudge from activities where Date = ?");
//        query.bindValue(0,d);
//        if(!query.exec())
//            qDebug() << query.lastError().text() << query.lastQuery();
//        model->setQuery(query);
//        float total = 0,avg;
//        for(int j=0;j<model->rowCount();j++)
//        {
//            QModelIndex indexType = model->index(j,1);
//            float score = indexType.data().toFloat();
//            total+=score;
//        }
//        if(model->rowCount()>0)
//        {
//            avg = (total/model->rowCount());

//            float yaxis = 900-(avg/10.0)*500;
//            QPen linepen(Qt::blue);
//            linepen.setCapStyle(Qt::RoundCap);
//            linepen.setWidth(10);
//            painter.setPen(linepen);
//            painter.drawPoint(x,yaxis);
//            points.push_back(std::make_pair (x,yaxis));
//        }
//            x+=xdiff;
//    }
//    for(int i=0;i<points.size()-1;i++)
//    {
//        QPen linepen1;
//        linepen1.setWidth(3);
//        if(points[i].second<points[i+1].second)
//            linepen1.setColor(Qt::red);
//        else
//            linepen1.setColor(QColor(0, 122, 22));

//        painter.setPen(linepen1);
//        painter.drawLine(points[i].first,points[i].second,points[i+1].first,points[i+1].second);
//    }
}

LineChart::~LineChart()
{
    delete ui;
}
