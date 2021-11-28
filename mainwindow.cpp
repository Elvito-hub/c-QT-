#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    ui->centralWidget->setStyleSheet("background-image: url(:/rsc/imgs/mainimg.jpg);"
                                     "background-position: center;"
                                    );
    ui->widget->setMaximumSize(400,500);
    ui->widget->setStyleSheet("background-image:url(:/rsc/imgs/backgimg.jfif);"
                              "border: 3px solid black;"
                              "border-radius: 10px;"
                              "font-size:30px");
    ptrCalendActs =NULL;
    ptrTodayActs = NULL;
    ptrProgFall = NULL;
    ptrRoadmaps = NULL;


}

MainWindow::~MainWindow()
{
    delete ui;
    if(ptrTodayActs)
    {
        delete ptrTodayActs;
        ptrTodayActs = NULL;
    }
    if(ptrCalendActs)
    {
        delete ptrCalendActs;
        ptrCalendActs = NULL;
    }
    if(ptrProgFall)
    {
        delete ptrProgFall;
        ptrProgFall = NULL;
    }
    if(ptrRoadmaps)
    {
        delete ptrRoadmaps;
        ptrRoadmaps = NULL;
    }
}

void MainWindow::on_actionToday_triggered()
{
    ui->centralWidget->hide();
    if(ptrCalendActs)
    {
        delete ptrCalendActs;
        ptrCalendActs = NULL;
    }
    if(ptrProgFall)
    {
        delete ptrProgFall;
        ptrProgFall = NULL;
    }
    if(ptrRoadmaps)
    {
        delete ptrRoadmaps;
        ptrRoadmaps = NULL;
    }
    if(!ptrTodayActs)
    ptrTodayActs = new Today_Acts(this);
    ptrTodayActs->show();
    ptrTodayActs->setGeometry(0,100,2100,1300);
}

void MainWindow::on_actionCalendar_triggered()
{
    ui->centralWidget->hide();
    if(ptrTodayActs)
    {
        delete ptrTodayActs;
        ptrTodayActs = NULL;
    }
    if(ptrProgFall)
    {
        delete ptrProgFall;
        ptrProgFall = NULL;
    }
    if(ptrRoadmaps)
    {
        delete ptrRoadmaps;
        ptrRoadmaps = NULL;
    }
    if(!ptrCalendActs)
    ptrCalendActs = new Calendar_Acts(this);
    ptrCalendActs->show();
    ptrCalendActs->setGeometry(0,100,2100,1300);
}

void MainWindow::on_actionProgress_Fall_triggered()
{
    ui->centralWidget->hide();
    if(ptrCalendActs)
    {
        delete ptrCalendActs;
        ptrCalendActs = NULL;
    }
    if(ptrTodayActs)
    {
        delete ptrTodayActs;
        ptrTodayActs = NULL;
    }
    if(ptrRoadmaps)
    {
        delete ptrRoadmaps;
        ptrRoadmaps = NULL;
    }
    if(!ptrProgFall)
    ptrProgFall = new ProgressFallWidget(this);
    ptrProgFall->show();
    ptrProgFall->setGeometry(0,100,2100,1300);
}
void MainWindow::on_Today_button_4_clicked()
{
    ui->centralWidget->hide();
    if(ptrCalendActs)
    {
        delete ptrCalendActs;
        ptrCalendActs = NULL;
    }
    if(ptrProgFall)
    {
        delete ptrProgFall;
        ptrProgFall = NULL;
    }
    if(ptrRoadmaps)
    {
        delete ptrRoadmaps;
        ptrRoadmaps = NULL;
    }
    if(!ptrTodayActs)
    ptrTodayActs = new Today_Acts(this);
    ptrTodayActs->show();
    ptrTodayActs->setGeometry(0,100,2100,1300);
}

void MainWindow::on_calendar_button_4_clicked()
{
    ui->centralWidget->hide();
    if(ptrTodayActs)
    {
        delete ptrTodayActs;
        ptrTodayActs = NULL;
    }
    if(ptrProgFall)
    {
        delete ptrProgFall;
        ptrProgFall = NULL;
    }
    if(ptrRoadmaps)
    {
        delete ptrRoadmaps;
        ptrRoadmaps = NULL;
    }
    if(!ptrCalendActs)
    ptrCalendActs = new Calendar_Acts(this);
    ptrCalendActs->show();
    ptrCalendActs->setGeometry(0,100,2100,1300);
}

void MainWindow::on_progress_button_4_clicked()
{
    ui->centralWidget->hide();
    if(ptrCalendActs)
    {
        delete ptrCalendActs;
        ptrCalendActs = NULL;
    }
    if(ptrTodayActs)
    {
        delete ptrTodayActs;
        ptrTodayActs = NULL;
    }
    if(ptrRoadmaps)
    {
        delete ptrRoadmaps;
        ptrRoadmaps = NULL;
    }
    if(!ptrProgFall)
    ptrProgFall = new ProgressFallWidget(this);
    ptrProgFall->show();
    ptrProgFall->setGeometry(0,100,2100,1300);
}





void MainWindow::on_roadmap_button_clicked()
{
    ui->centralWidget->hide();
    if(ptrCalendActs)
    {
        delete ptrCalendActs;
        ptrCalendActs = NULL;
    }
    if(ptrTodayActs)
    {
        delete ptrTodayActs;
        ptrTodayActs = NULL;
    }
    if(ptrProgFall)
    {
        delete ptrProgFall;
        ptrProgFall = NULL;
    }
    if(!ptrRoadmaps)
    ptrRoadmaps = new Roadmaps(this);
    ptrRoadmaps->show();
    ptrRoadmaps->setGeometry(0,100,2100,1300);
}

void MainWindow::on_actionroadmap_triggered()
{
    ui->centralWidget->hide();
    if(ptrCalendActs)
    {
        delete ptrCalendActs;
        ptrCalendActs = NULL;
    }
    if(ptrTodayActs)
    {
        delete ptrTodayActs;
        ptrTodayActs = NULL;
    }
    if(ptrProgFall)
    {
        delete ptrProgFall;
        ptrProgFall = NULL;
    }
    if(!ptrRoadmaps)
    ptrRoadmaps = new Roadmaps(this);
    ptrRoadmaps->show();
    ptrRoadmaps->setGeometry(0,100,2100,1300);
}
