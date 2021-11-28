#include "addactivity.h"
#include "ui_addactivity.h"
#include<QTime>
#include<QDate>

AddActivity::AddActivity(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddActivity)
{
    ui->setupUi(this);
    this->setMinimumSize(500,500);
    ui->line->setMinimumWidth(1000);
    postbutton = new QPushButton("Add activity",this);
    postbutton->setGeometry(250,250,150,50);
    connect(postbutton,SIGNAL(clicked(bool)),this,SLOT(on_pushButton_clicked()));

}

AddActivity::~AddActivity()
{
    delete ui;
}
void AddActivity::Show()
{
    this->show();
}

void AddActivity::on_pushButton_clicked()
{
    ui->label_info->setText("");
    QString sName = ui->lineEdit->text();
    QString sType = ui->comboBox->currentText();
    QTime time1 = ui->timeStart->time();
    QString sTimeStart = time1.toString("hh:mm");
    QTime time2 = ui->timeFinish->time();
    QString sTimeFinish = time2.toString("hh:mm");
    QString timeRange = sTimeStart+'-'+sTimeFinish;
    QDate date = QDate::currentDate();
    QString theDate = date.toString("yyyy-MM-dd");

    QSqlQuery query(MyDB::getInstance1()->getDBInstance1());
    query.clear();
    query.prepare("insert into activities(Name,Type,TimeRange,StatusJudge,Date) values('"+sName+"','"+sType+"','"+timeRange+"','','"+theDate+"')");
    if(!query.exec())
        ui->label_info->setText("unable to add activity");
    else
    {
        if(query.numRowsAffected()>0)
        {
            ui->label_info->setText("activity added successfully");
            resetElements();
            this->hide();
        }else
            qDebug() << "unable to add item";
    }
}
void AddActivity::resetElements()
{
    ui->lineEdit->clear();
    ui->label_info->clear();
}
