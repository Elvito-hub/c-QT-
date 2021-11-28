#include "addroadmap.h"
#include "ui_addroadmap.h"
#include<QDebug>

AddRoadmap::AddRoadmap(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRoadmap)
{
    ui->setupUi(this);
    this->setMinimumSize(900,600);
    ui->label->setGeometry(200,30,400,40);
    ui->label->setStyleSheet("padding-left:150px");
    postbutton = new QPushButton("Add Roadmap",this);
    postbutton->setGeometry(650,555,150,40);
    connect(postbutton,SIGNAL(clicked()),this,SLOT(on_pushButton_clicked()));
    QDateTime t1 = QDateTime::currentDateTime();
    ui->dateTimeEdit->setDateTime(t1);
    ui->dateTimeEdit_2->setDateTime(t1);
}

void AddRoadmap::resetElements()
{
    ui->lineEdit->clear();
    ui->textEdit->clear();
    ui->label_info->clear();
}



AddRoadmap::~AddRoadmap()
{
    delete ui;
}

void AddRoadmap::on_pushButton_clicked()
{
    QString title = ui->lineEdit->text();
    QString roadmap = ui->textEdit->toPlainText();
    QDateTime startT = ui->dateTimeEdit->dateTime();
    QDateTime finishT = ui->dateTimeEdit_2->dateTime();
    QString startTime = startT.toString("yyyy-MM-dd-hh:mm");
    QString finishTime = finishT.toString("yyyy-MM-dd-hh:mm");
    QString type = ui->comboBox->currentText();

    qDebug()<<title;
    qDebug()<<roadmap;
    qDebug()<<startTime;
    qDebug()<<finishTime;
    QSqlQuery query(Mydbrm::getInstance()->getDBInstance());
    query.clear();
    int step = 0;
    query.prepare(QString("insert into roadmaps(title,roadmap,step,type,startTime,endTime) values('"+title+"','"+roadmap+"',%1,'"+type+"','"+startTime+"','"+finishTime+"')").arg(step));
    if(!query.exec())
        ui->label_info->setText("unable to add activity");
    else
    {
        if(query.numRowsAffected()>0)
        {
            ui->label_info->setText("activity added successfully");
            this->hide();
            resetElements();
        }else
            qDebug() << "unable to add item";
    }

}
