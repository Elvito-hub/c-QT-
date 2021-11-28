#include "piechartdrawer.h"
#include<QPainter>
#include<QDate>
#include<QDebug>

PieChartDrawer::PieChartDrawer(QWidget *parent)
    :QWidget(parent)
{
    resize(200,200);
}

PieChartDrawer::~PieChartDrawer()
{
}

void PieChartDrawer::paintEvent(QPaintEvent *)
{
    //load model for our TableView
    QSqlQueryModel *model = new QSqlQueryModel(this);
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    QDate date = QDate::currentDate();
    QString theDate = date.toString("yyyy-MM-dd");
    query.prepare("select Name,Type,TimeRange,StatusJudge from activities where Date =?");
    query.bindValue(0,theDate);

    if(!query.exec())
        qDebug() << query.lastError().text() << query.lastQuery();
    float academ = 0;
    float selfDev = 0;
    float health = 0;
    float social = 0;
    qDebug()<<model->rowCount();
    for(int i=0;i<model->rowCount();i++)
    {
        QModelIndex indexType = model->index(i,1);
        QString type = indexType.data().toString();
        QModelIndex indexTimeRange = model->index(i,2);
        QString timeRange = indexTimeRange.data().toString();
        float st = timeRange.mid(0,2).toFloat() + timeRange.mid(3,2).toFloat()/60;
        float ft = timeRange.mid(6,2).toFloat() + timeRange.mid(9,2).toFloat()/60;
        qDebug()<<"here";
        if(type=="学术的")
            academ+=(ft-st);
        else if(type=="自我发展")
            selfDev+=(ft-st);
        else if(type=="健康的")
            health+=(ft-st);
        else if(type=="社会的")
            social+=(ft-st);
    }
    float tot = academ+selfDev+health+social;
    QPainter painter(this);
    // Set Brush
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    painter.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
    QRectF rectangle(0, 0, 200.0,200.0);
    float startAngle = 0.0;
    float spanAngle = (360*academ)/tot;
    painter.drawPie(rectangle, startAngle, spanAngle);
    painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
    float startAngle1 = (360*academ)/tot;
    float spanAngle1 = (360*health)/tot;
    painter.drawPie(rectangle, startAngle1, spanAngle1);
}

