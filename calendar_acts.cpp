#include "calendar_acts.h"
#include "ui_calendar_acts.h"
#include<QIcon>
#include<QSize>
#include<QWidget>
#include<QPushButton>
#include<QLineEdit>
#include<QDebug>
#include<QDate>

Calendar_Acts::Calendar_Acts(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Calendar_Acts)
{
    ui->setupUi(this);
    ui->pushButton->setMinimumSize(80,80);
    ui->pushButton->setIcon(QIcon(":/menubar/imgs/calendar.svg"));
    ui->pushButton->setIconSize(QSize(50,50));

    ui->label_3->setStyleSheet("font-size:30px;"
                             "border:2px solid black;"
                             "margin-left:300%;"
                             "border-radius:10px;"
                             "margin-top:40px");
    ui->label_3->setMaximumHeight(200);
    ui->label_3->setGeometry(100,100,1000,200);


    table = new QTableView(this);
    table->setGeometry(320,500,1100,400);

    ui->label_5->setStyleSheet("font-size:30px;"
                               "border:2px solid black;"
                               );
    ui->label_5->setGeometry(1200,100,400,50);
    QDate date = QDate::currentDate();
    QString theDate = date.toString("yyyy-MM-dd");
    calendar = NULL;
    updateTable(theDate);
    ptrPolarchart = new PolarChart(this);
    ptrPolarchart->setGeometry(1450,500,1000,1000);
    ptrPolarchart->thDate = theDate;
    ptrPolarchart->show();
}





Calendar_Acts::~Calendar_Acts()
{
    delete ui;
    delete ptrPolarchart;
}

void Calendar_Acts::on_pushButton_clicked()
{
    if(!calendar)
    {
        calendar = new QCalendarWidget(this);
        calendar->show();
        calendar->setGeometry(150,50,600,400);
        connect(calendar,SIGNAL(activated(QDate)),this,SLOT(onChoseDay(QDate)));

    }else{
        delete calendar;
        calendar = NULL;
    }
}

void Calendar_Acts::onChoseDay(const QDate &date)
{
    QString sdate = date.toString("yyyy-MM-dd");
    ptrPolarchart->thDate = sdate;
    ptrPolarchart->update();
    updateTable(sdate);
    delete calendar;
    calendar = NULL;
}

void Calendar_Acts::updateTable(QString sdate)
{

    ui->label_5->setText("日期 ： " + sdate);
    //load model for our TableView
    QSqlQueryModel *model = new QSqlQueryModel(this);
    QSqlQuery query(MyDB::getInstance1()->getDBInstance1());
    query.prepare("select Name,Type,TimeRange,StatusJudge from activities where Date =?");
    query.bindValue(0,sdate);
    if(!query.exec())
        qDebug() << query.lastError().text() << query.lastQuery();
    else
        qDebug() << "== success query fetch";
    model->setQuery(query);
    qDebug()<<"rows are : "<<model->rowCount();
    int n=model->rowCount();
    ui->label_3->setText("  Number of Activities : " + QString::number(n));
    table->setModel(model);
    table->setItemDelegate(new Delegate);
    table->setStyleSheet("QHeaderView::section { background-color:rgba(246, 200, 193, 0.8) }");

    for(int i=0;i<model->rowCount();i++)
    {
        QModelIndex index = model->index(i,0);
        QString name = index.data().toString();
        QWidget *statusjudgewidg= new QWidget(this);
        QPushButton *button =new QPushButton("Judge",statusjudgewidg);
        QLabel *points = new QLabel(statusjudgewidg);
        points->setGeometry(23,1.7,120,40);
        points->setText("/ 10");
        button->setGeometry(150,1,100,40);
        table->setIndexWidget(model->index(i,3),statusjudgewidg);
        connect(button,&QPushButton::clicked,[this,name,sdate](){
            updateStatusJudge(name,sdate);
        });
    }
    table->show();
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void Calendar_Acts::updateStatusJudge(const QString name, const QString date)
{
    QDialog *judgeActivity = new QDialog(this);
    judgeActivity->setWindowTitle("Judge Activity");
    judgeActivity->setMinimumSize(300,150);
    QLabel *title = new QLabel("Score: ", judgeActivity);
    title->setStyleSheet("font-size:25px");
    title->setGeometry(10,30,70,50);
    QLineEdit *scoreInput = new QLineEdit(judgeActivity);
    scoreInput->setGeometry(100,30,100,50);
    QLabel *maxScore = new QLabel("/10", judgeActivity);
    maxScore->setStyleSheet("font-size:25px;"
                            "border:1px solid black;");
    maxScore->setGeometry(210,30,50,50);
    QPushButton *judgeButton = new QPushButton("Judge",judgeActivity);
    judgeButton->setGeometry(160,100,100,40);
    connect(judgeButton,&QPushButton::clicked,[this,name,date,scoreInput,judgeActivity](){
        int actScore = scoreInput->text().toInt();
       QSqlQuery query(MyDB::getInstance1()->getDBInstance1());
       query.prepare(QString("UPDATE activities SET StatusJudge=%1 where Name =='"+name+"' AND Date=='"+date+"' ").arg(actScore));
       if(!query.exec())
       {
          qDebug() << query.lastError().text() << query.lastQuery();
       }else{
           qDebug() << "updated";
       }
       delete judgeActivity;
       updateTable(date);
       ptrPolarchart->update();
    });
    judgeActivity->show();
}

