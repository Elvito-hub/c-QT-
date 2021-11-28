#include "today_acts.h"
#include "ui_today_acts.h"

#include<QMessageBox>
#include<QScreen>
#include<QRect>
#include<QDate>
#include<QDebug>
#include<QTimer>

Today_Acts::Today_Acts(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Today_Acts)
{
    ui->setupUi(this);
    ptrAddActivity = new AddActivity(this);
    connect(ptrAddActivity->postbutton,SIGNAL(clicked()),this,SLOT(updateUi()));
    updateUi();
    this->setMinimumSize(2100,1300);
    ui->label_3->setStyleSheet("font-size:30px;"
                             "border:2px solid black;"
                             "margin-left:300%;"
                             "border-radius:10px;"
                             "margin-top:40px");
    ui->label_3->setMaximumHeight(200);
    button = new QPushButton("添加任务",this);
    button->setGeometry(1290,420,200,70);
    button->setStyleSheet("font-size:20px;");

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
    ptrPiechart = new PieChart(this);
    ptrPiechart->show();
    ptrPiechart->setGeometry(1600,500,400,800);
    //ptrPiechart->setStyleSheet("border:5px solid black;");

}

Today_Acts::~Today_Acts()
{
    delete ui;
    delete ptrAddActivity;
    delete ptrPiechart;
}

void Today_Acts::showAddAct()
{
    ptrAddActivity->Show();

}
void Today_Acts::updateUi()
{

    table = new QTableView(this);
    QDate date = QDate::currentDate();
    //load model for our TableView
    QSqlQueryModel *model= new QSqlQueryModel(this);
    model = fetch(date);
    qDebug()<<"rows are : "<<model->rowCount();
    int n=model->rowCount();
    ui->label_3->setText("  Number of Activities : " + QString::number(n));
    table->setGeometry(250,500,1250,500);
    table->setModel(model);
    table->setStyleSheet("QHeaderView::section { background-color:red; }");
    table->setItemDelegate(new Delegate);
    QString theDate = date.toString("yyyy-MM-dd");
    for(int i=0;i<model->rowCount();i++)
    {
        QModelIndex index = model->index(i,0);
        QString name = index.data().toString();
        QWidget *statusjudgewid= new QWidget(this);
        QPushButton *button =new QPushButton("Judge",statusjudgewid);
        QLabel *points = new QLabel(statusjudgewid);
        points->setGeometry(23,1.7,120,40);
        points->setText("/ 10");
        button->setGeometry(190,1,100,40);
        table->setIndexWidget(model->index(i,3),statusjudgewid);
        connect(button,&QPushButton::clicked,[this,name,theDate](){
            updateStatusJudge(name,theDate);
        });
        QModelIndex indexType = model->index(i,1);
        QString type = indexType.data().toString();
        //if(type=="学术的")
        //qDebug()<<i;

    }

    table->show();
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void Today_Acts::updateStatusJudge(const QString name,const QString date)
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
       updateUi();
    });
    judgeActivity->show();
}

QSqlQueryModel* Today_Acts::fetch(QDate date)
{
    //load model for our TableView
    QSqlQueryModel *model = new QSqlQueryModel(this);
    QSqlQuery query(MyDB::getInstance1()->getDBInstance1());
    QString theDate = date.toString("yyyy-MM-dd");
    query.prepare("select Name,Type,TimeRange,StatusJudge from activities where Date =?");
    query.bindValue(0,theDate);
    if(!query.exec())
        qDebug() << query.lastError().text() << query.lastQuery();
    model->setQuery(query);
    return model;
}







