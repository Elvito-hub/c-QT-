#include "piechart.h"
#include "ui_piechart.h"
#include<QDate>
#include<QPainter>

PieChart::PieChart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PieChart)
{
    ui->setupUi(this);
    resize(1000,1000);
}

PieChart::~PieChart()
{
    delete ui;
}
void PieChart::paintEvent(QPaintEvent *){

    QPainter painter(this);
    //load model for our TableView
    QSqlQueryModel *model = new QSqlQueryModel(this);
    QSqlQuery query(MyDB::getInstance1()->getDBInstance1());
    QDate date = QDate::currentDate();
    QString theDate = date.toString("yyyy-MM-dd");
    query.prepare("select Name,Type,TimeRange,StatusJudge from activities where Date =?");
    query.bindValue(0,theDate);

    if(!query.exec())
        qDebug() << query.lastError().text() << query.lastQuery();
    model->setQuery(query);
    float academ = 0;
    float selfDev = 0;
    float health = 0;
    float social = 0;
    for(int i=0;i<model->rowCount();i++)
    {
        QModelIndex indexType = model->index(i,1);
        QString type = indexType.data().toString();
        QModelIndex indexTimeRange = model->index(i,2);
        QString timeRange = indexTimeRange.data().toString();
        float st = timeRange.mid(0,2).toFloat() + timeRange.mid(3,2).toFloat()/60;
        float ft = timeRange.mid(6,2).toFloat() + timeRange.mid(9,2).toFloat()/60;
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
    if(tot)
    {

        // Set Brush
        painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
        painter.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
        QRectF rectangle(50, 50, 200.0,200.0);
        float startAngle = 0.0*16;
        float spanAngle = ((360*academ)/tot)*16;
        painter.drawPie(rectangle, startAngle, spanAngle);


        painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
        float startAngle1 = ((360*academ)/tot)*16;
        float spanAngle1 = ((360*health)/tot)*16;
        painter.drawPie(rectangle, startAngle1, spanAngle1);

        painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
        float startAngle2 = ((360*health)/tot)*16+startAngle1;
        float spanAngle2 = ((360*selfDev)/tot)*16;
        painter.drawPie(rectangle, startAngle2, spanAngle2);

        painter.setBrush(QBrush(Qt::yellow, Qt::SolidPattern));
        float startAngle3 = ((360*selfDev)/tot)*16+startAngle2;
        float spanAngle3 = ((360*social)/tot)*16;
        painter.drawPie(rectangle, startAngle3, spanAngle3);


        painter.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
        painter.drawEllipse(50,280,15,15);
        QRectF rectangle1(90, 278, 100,50);
        painter.drawText(rectangle1,"： 学术的");
        painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
        painter.drawEllipse(50,330,15,15);
        QRectF rectangle2(90, 328, 100,50);
        painter.drawText(rectangle2,"： 健康的");
        painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
        painter.drawEllipse(50,380,15,15);
        QRectF rectangle3(90, 378, 100,50);
        painter.drawText(rectangle3,"： 自我发展");
        painter.setBrush(QBrush(Qt::yellow, Qt::SolidPattern));
        painter.drawEllipse(50,430,15,15);
        QRectF rectangle4(90, 428, 100,50);
        painter.drawText(rectangle4,"： 社会的");

        //border
        painter.setPen(Qt::black);
        painter.drawLine(0,0,0,500);
        painter.drawLine(0,500,300,500);
        painter.drawLine(300,500,300,0);
        painter.drawLine(300,0,0,0);
    }

}
