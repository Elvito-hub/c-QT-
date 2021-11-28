#include "progressfallwidget.h"
#include "ui_progressfallwidget.h"
#include<QDate>
#include<QPixmap>

ProgressFallWidget::ProgressFallWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProgressFallWidget)
{
    ui->setupUi(this);
    this->setMinimumSize(2100,1300);
    ui->label_3->setGeometry(800,30,500,50);
    ui->dateEdit->setMinimumSize(200,50);
    ui->dateEdit_2->setMinimumSize(200,50);
    QDate date = QDate::currentDate();
    int datejul = date.toJulianDay()-1;
    date = QDate::fromJulianDay(datejul);
    ui->dateEdit_2->setDate(date);
    QString theDate = date.toString("yyyy-MM-dd");
    QString startDate = getStartDate(theDate);
    QDate Date1 = QDate::fromString(startDate,"yyyy-MM-dd");
    ui->dateEdit->setDate(Date1);
    ptrLineChart = new LineChart(this);
    ptrLineChart->setGeometry(100,100,1900,1000);
    ptrLineChart->jul1 = Date1.toJulianDay();
    ptrLineChart->jul2 = date.toJulianDay();
    qDebug()<<ptrLineChart->jul1<<" "<<ptrLineChart->jul2<<"  ok dates";
    ptrLineChart->show();
    connect(ui->dateEdit,SIGNAL(dateChanged(QDate)),this,SLOT(updateDiff()));
    connect(ui->dateEdit_2,SIGNAL(dateChanged(QDate)),this,SLOT(updateDiff()));
}

ProgressFallWidget::~ProgressFallWidget()
{
    delete ui;
    delete ptrLineChart;
}

QString ProgressFallWidget::getStartDate(QString date)
{
    QDate date1 = QDate::fromString(date,"yyyy-MM-dd");
    int date00 = date1.toJulianDay()-7;
    QDate date0 = QDate::fromJulianDay(date00);
    QString newDate = date0.toString("yyyy-MM-dd");
    return newDate;

}

void ProgressFallWidget::updateDiff()
{
    QDate date1 = ui->dateEdit->date();
    QDate date2 = ui->dateEdit_2->date();
    float differ = date2.toJulianDay()-date1.toJulianDay();
    ptrLineChart->diff = differ;
    ptrLineChart->jul1 = date1.toJulianDay();
    ptrLineChart->jul2 = date2.toJulianDay();
    ptrLineChart->update();
}


