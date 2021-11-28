#include "roadmapdraw.h"
#include "ui_roadmapdraw.h"
#include<QDate>
#include<bits/stdc++.h>

RoadmapDraw::RoadmapDraw(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RoadmapDraw)
{
    ui->setupUi(this);
    this->setMinimumSize(1500,900);
    this->setProperty("mandi",true);
    nextStep = new QPushButton("Step",this);
    nextStep->setGeometry(1300,80,100,40);
    nextStep->setProperty("mandatoryFielde", true);
    connect(nextStep,SIGNAL(clicked(bool)),this,SLOT(updateStep()));
}

void RoadmapDraw::Show()
{
    this->show();
    ui->label->setText(title);
    ui->label->setGeometry(600,50,200,30);
    ui->label->setStyleSheet("font-size:30px;"
                             "text-decoration:underline;");
    ui->label_2->setText("Remaining days : ");
    ui->label_2->setGeometry(100,100,200,30);
    ui->label_2->setStyleSheet("font-size:20px;");



}

void RoadmapDraw::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //load model for our TableView
    QSqlQueryModel *model = new QSqlQueryModel(this);
    QSqlQuery query(Mydbrm::getInstance()->getDBInstance());
    query.prepare("select roadmap,step,type,startTime,endTime from roadmaps where title =?");
    query.bindValue(0,title);
    if(!query.exec())
        qDebug() << query.lastError().text() << query.lastQuery();
    model->setQuery(query);
    QModelIndex rm = model->index(0,0);
    QModelIndex stp = model->index(0,1);

    QDate date = QDate::currentDate();
    QString todaydate = date.toString("yyyy-MM-dd");
    QModelIndex finalDate = model->index(0,4);
    QString finald = finalDate.data().toString();
    QString finald1 = finald.mid(0,10);
    QDate Date1 = QDate::fromString(todaydate,"yyyy-MM-dd");
    QDate Date2 = QDate::fromString(finald1,"yyyy-MM-dd");
    int dif = Date2.toJulianDay()-Date1.toJulianDay();
    QString s = QString::number(dif);
    s.append(" days");
    ui->label_3->setText(s);
    QDate date3 = QDate::currentDate();

    ui->label_3->setGeometry(259,101,200,30);

    ui->label_3->setStyleSheet("font-size:20px;");
    QPixmap pixmap1(":/rsc/imgs/walk.png");
    QPixmap pixmap2(":/rsc/imgs/award.png");

    painter.drawPixmap(35+(step*100),770-(step*50),80,80, pixmap1);

    painter.drawPixmap(97+(totStep*100),800-(totStep*50),50,50,pixmap2);
    step= stp.data().toInt();
    QString theRm = rm.data().toString();
    std::vector<QString> str;
    QStringList lines = theRm.split( "\n", QString::SkipEmptyParts );
    foreach( QString line, lines ) {
       str.push_back(line);
    }
    totStep = str.size();
    for(unsigned int i=0;i<str.size();i++)
    {
        if(i<step)
        {
            painter.setBrush(Qt::green);
            painter.setPen(Qt::black);
        }else
        {
            painter.setBrush(Qt::lightGray);
            painter.setPen(Qt::black);
        }
        QRectF rect = QRectF((i*100)+100,800-(i*50),1000,50);
        painter.drawRect(rect);

        painter.setFont(QFont(painter.font().family(), 10));
        painter.drawText(rect,Qt::AlignVCenter,str[i]);
    }
}

RoadmapDraw::~RoadmapDraw()
{
    delete ui;
}

void RoadmapDraw::updateStep()
{
    QSqlQuery query(Mydbrm::getInstance()->getDBInstance());
    if(step<totStep)
    {
        step++;
    }
    query.prepare(QString("UPDATE roadmaps SET step=%1 where title =='"+title+"' ").arg(step));
    if(!query.exec())
    {
       qDebug() << query.lastError().text() << query.lastQuery();

    }else{
        qDebug() << "updated";
        this->update();
    }
}
