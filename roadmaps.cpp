#include "roadmaps.h"
#include "ui_roadmaps.h"

#include<bits/stdc++.h>
#include<QWidget>
#include<QLabel>
#include<QPushButton>
#include<QDate>
#include<QTimer>

Roadmaps::Roadmaps(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Roadmaps)
{
    ui->setupUi(this);
    ui->pushButton->setGeometry(1600,30,200,60);
    ui->label->setGeometry(850,90,200,60);
    updateRmUi();

    ptraddrm = new AddRoadmap(this);
    ptrmdraw = new RoadmapDraw(this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(showAddrm()));
    connect(ptraddrm->postbutton,SIGNAL(clicked()),this,SLOT(updateRmUi()));
    connect(ptrmdraw->nextStep,SIGNAL(clicked()),this,SLOT(updateRmUi()));
}

void Roadmaps::updateRmUi()
{
    this->update();
    QSqlQueryModel *model = new QSqlQueryModel(this);
    QSqlQuery query(Mydbrm::getInstance()->getDBInstance());
    query.prepare("select title,roadmap,step,type,startTime,endTime from roadmaps");

    if(!query.exec())
        qDebug() << query.lastError().text() << query.lastQuery();
    model->setQuery(query);
    int n = model->rowCount();
    qDebug()<<n<<" rows";


    for(int i=0;i<n;i++)
    {
        int x;
        int y=i/3;
        if(i%3==0)
            x=300;
        else if(i%3==1)
            x=900;
        else if(i%3==2)
            x=1500;


        QWidget *rmWidget = new QWidget(this);
        QLabel *rmLabel = new QLabel(rmWidget);
        rmLabel->setText("Plan Title: ");
        QLabel *rmTitle = new QLabel(rmWidget);
        QModelIndex titleIndex = model->index(i,0);
        QString title = titleIndex.data().toString();
        rmTitle->setText(title);
        QModelIndex endTime = model->index(i,5);

        QString endtime = endTime.data().toString();
        QString endt = endtime.mid(0,10);
        QDate lastd = QDate::fromString(endt,"yyyy-MM-dd");
        QDate tod = QDate::currentDate();
        int jin = tod.toJulianDay();
        int last = lastd.toJulianDay();


        QPushButton *viewButton = new QPushButton("view",rmWidget);
        rmWidget->setProperty("mandatoryField", true);
        rmWidget->setGeometry(x,300+(y*250),400,150);
        rmWidget->show();
        qDebug()<<"here "<<jin<<" "<<last;

        QModelIndex rm = model->index(i,1);
        QModelIndex stp = model->index(i,2);
        int curstp = stp.data().toInt();
        QString theRm = rm.data().toString();
        std::vector<QString> str;
        QStringList lines = theRm.split( "\n", QString::SkipEmptyParts );
        int nbrstps = lines.size();

        if(jin>last && nbrstps>curstp)
        {
            QTimer *timer = new QTimer(this);
            int flag=1;
            rmWidget->setStyleSheet("background-color:black;"
                                    "color:white;");
            connect(timer,&QTimer::timeout,[rmWidget,flag](){
                QString sty = rmWidget->styleSheet();
                if(sty=="background-color:black;color:white;")
                    rmWidget->setStyleSheet("background-color:white;color:black;");
                else
                    rmWidget->setStyleSheet("background-color:black;color:white;");

            });
            timer->start(1000);
        }else if(nbrstps == curstp)
        {
            rmWidget->setStyleSheet("background-image:url(:/rsc/imgs/checked.png);"
                                    "background-size: cover; "
                                    "background-repeat: no-repeat;"
                                    "background-position: center center;");
            rmLabel->setStyleSheet("background-image:url(:/rsc/imgs/backgimg.jfif)");
            rmTitle->setStyleSheet("background-image:url(:/rsc/imgs/backgimg.jfif)");
        }
        rmLabel->setGeometry(50,20,120,40);
        rmLabel->setStyleSheet("font-size:25px;");
        rmTitle->setGeometry(170,20,200,40);
        rmTitle->setStyleSheet("font-size:20px;"
                               "font-weight:bold;");
        viewButton->setGeometry(180,100,100,30);
        connect(viewButton,&QPushButton::clicked,[this,title](){
            showRmDraw(title);
        });
    }

}



void Roadmaps::showAddrm()
{
    ptraddrm->show();
}

void Roadmaps::showRmDraw(QString title)
{
    qDebug()<< title;
    ptrmdraw->title = title;
    ptrmdraw->Show();
}

Roadmaps::~Roadmaps()
{
    delete ui;
    delete ptraddrm;
    delete ptrmdraw;
}
