#include "polarchart.h"
#include "ui_polarchart.h"
#include<QDebug>

PolarChart::PolarChart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PolarChart)
{
    ui->setupUi(this);
    resize(1000,1000);
}


void PolarChart::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    //load model for our TableView
    QSqlQueryModel *model = new QSqlQueryModel(this);
    QSqlQuery query(MyDB::getInstance1()->getDBInstance1());
    query.prepare("select Name,Type,TimeRange,StatusJudge from activities where Date =?");
    query.bindValue(0,thDate);

    if(!query.exec())
        qDebug() << query.lastError().text() << query.lastQuery();
    model->setQuery(query);
    float academ = 0, nAca = 0;
    float selfDev = 0, nselfd = 0;
    float health = 0, nhealt = 0;
    float social = 0, nsoci = 0;

    for(int i=0;i<model->rowCount();i++)
    {
        QModelIndex indexType = model->index(i,1);
        QString type = indexType.data().toString();
        QModelIndex indexScore = model->index(i,3);
        float score = indexScore.data().toFloat();
        if(type=="学术的")
        {
            academ+=score;
            nAca++;
        }
        else if(type=="自我发展"){
            selfDev+=score;
            nselfd++;
        }
        else if(type=="健康的")
        {
            health+=score;
            nhealt++;
        }
        else if(type=="社会的")
        {
            social+=score;
            nsoci++;
        }
    }
    if(academ)
           academ = (academ/(nAca*10.0))*400.0;
    if(selfDev)
        selfDev = (selfDev/(nselfd*10.0))*400.0;
    if(health)
        health = (health/(nhealt*10.0))*400.0;
    if(social)
        social = (social/(nsoci*10.0))*400.0;
    float total = academ + selfDev + health + social;

    if(total>0)
    {



    painter.setPen(Qt::black);
    painter.drawEllipse(270,240,80,80);
    painter.drawText(300,240,"20");
    painter.drawEllipse(230,200,160,160);
    painter.drawText(300,200,"40");
    painter.drawEllipse(190,160,240,240);
    painter.drawText(300,160,"60");
    painter.drawEllipse(150,120,320,320);
    painter.drawText(300,120,"80");
    painter.drawEllipse(110,80,400,400);
    painter.drawText(295,80,"100");


    // Set Brush
    painter.setPen(QPen(Qt::white, 1, Qt::SolidLine, Qt::FlatCap));
    QColor color1 = Qt::blue;
    color1.setAlphaF(0.7);
    painter.setBrush(color1);
    float recX = (310-(academ/80.0)*40.0);
    float recY = (280-(academ/80.0)*40.0);
    QRectF rectangle(recX,recY,academ,academ);
    float startAngle = 0.0*16;
    float spanAngle = (360.0/4.0)*16.0;
    painter.drawPie(rectangle, startAngle, spanAngle);

    painter.setPen(QPen(Qt::white, 1, Qt::SolidLine, Qt::FlatCap));
    QColor color2 = Qt::green;
    color2.setAlphaF(0.7);
    painter.setBrush(color2);
    recX = (310-(selfDev/80.0)*40.0);
    recY = (280-(selfDev/80.0)*40.0);
    QRectF rectangle1(recX,recY,selfDev,selfDev);
    startAngle = (360.0/4.0)*16.0;
    spanAngle = (360.0/4.0)*16.0;
    painter.drawPie(rectangle1, startAngle, spanAngle);


    painter.setPen(QPen(Qt::white, 1, Qt::SolidLine, Qt::FlatCap));
    QColor color3 = Qt::red;
    color3.setAlphaF(0.7);
    painter.setBrush(color3);
    recX = (310-(health/80.0)*40.0);
    recY = (280-(health/80.0)*40.0);
    QRectF rectangle2(recX,recY,health,health);
    startAngle = 2*(360.0/4.0)*16.0;
    spanAngle = (360.0/4.0)*16.0;
    painter.drawPie(rectangle2, startAngle, spanAngle);


    painter.setPen(QPen(Qt::white, 1, Qt::SolidLine, Qt::FlatCap));
    QColor color4 = Qt::yellow;
    color4.setAlphaF(0.7);
    painter.setBrush(color4);
    recX = (310-(social/80.0)*40.0);
    recY = (280-(social/80.0)*40.0);
    QRectF rectangle3(recX,recY,social,social);
    startAngle = 3*(360.0/4.0)*16.0;
    spanAngle = (360.0/4.0)*16.0;
    painter.drawPie(rectangle3, startAngle, spanAngle);
    painter.restore();

    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    painter.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
    painter.drawEllipse(50,530,15,15);
    QRectF rect(70, 528, 100,50);
    painter.drawText(rect,"： 学术的");
    painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
    painter.drawEllipse(190,530,15,15);
    QRectF rect1(210, 528, 100,50);
    painter.drawText(rect1,"： 健康的");
    painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
    painter.drawEllipse(330,530,15,15);
    QRectF rect2(350, 528, 100,50);
    painter.drawText(rect2,"： 自我发展");
    painter.setBrush(QBrush(Qt::yellow, Qt::SolidPattern));
    painter.drawEllipse(470,530,15,15);
    QRectF rect3(490, 528, 100,50);
    painter.drawText(rect3,"： 社会的");

    //border
    painter.setPen(Qt::black);
    painter.drawLine(0,0,0,620);
    painter.drawLine(0,620,600,620);
    painter.drawLine(600,620,600,0);
    painter.drawLine(600,0,0,0);
    }
}

PolarChart::~PolarChart()
{
    delete ui;
}
