#include "today_acts.h"
#include "ui_today_activities.h"

#include<QMessageBox>
#include<QScreen>
#include<QRect>
#include<QDate>
#include<QDebug>
#include<QTimer>

Today_Activities::Today_Activities(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Today_Activities)
{
    ui->setupUi(this);

    ptrAddActivity = new AddActivity(this);
    QTimer *timer= new QTimer(this);
    connect(timer,&QTimer::timeout,this,updateUi);
    timer->start(10000);
    updateUi();


    this->setMinimumSize(2100,1300);
    ui->label_3->setStyleSheet("font-size:30px;"
                             "border:2px solid black;"
                             "margin-left:300%;"
                             "border-radius:10px;"
                             "margin-top:40px");
    ui->label_3->setMaximumHeight(200);
    button = new QPushButton("添加任务",this);
    button->setGeometry(900,400,100,40);

    ui->label_5->setStyleSheet("font-size:30px;"
                               "border:2px solid black;"
                               "margin-bottom:240%");
    ui->label_5->setMaximumWidth(300);
    ui->label_5->setAlignment(Qt::AlignTop);
    QDate date = QDate::currentDate();
    QString theDate = date.toString("yyyy-MM-dd");
    ui->label_5->setText("今天 ： " + theDate);
    ui->widget_4->setMinimumSize(300,300);
    connect(button,SIGNAL(clicked()),this,SLOT(showAddAct()));
}

Today_Activities::~Today_Activities()
{
    delete ui;
    delete ptrAddActivity;
}

void Today_Activities::showAddAct()
{
    ptrAddActivity->show();
}
void Today_Activities::updateUi()
{

    table = new QTableView(this);
    table->setGeometry(320,500,1100,400);
    //load model for our TableView
    QSqlQueryModel *model = new QSqlQueryModel(this);
    QSqlQuery query(MyDB::getInstance()->getDBInstance());
    QDate date = QDate::currentDate();
    QString theDate = date.toString("yyyy-MM-dd");
    query.prepare("select Name,Type,TimeRange,StatusJudge from activities where Date =?");
    query.bindValue(0,theDate);

    if(!query.exec())
        qDebug() << query.lastError().text() << query.lastQuery();
    else
        qDebug() << "== success query fetch";
    model->setQuery(query);
    qDebug()<<"rows are : "<<model->rowCount();
    int n=model->rowCount();
    ui->label_3->setText("  Number of Activities : " + QString::number(n));
    table->setModel(model);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

