#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPushButton>
#include<QTableView>

#include "today_acts.h"
#include "calendar_acts.h"
#include "progressfallwidget.h"
#include "roadmaps.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void objectCreator();
    ~MainWindow();
private slots:
    void on_actionToday_triggered();

    void on_actionCalendar_triggered();

    void on_actionProgress_Fall_triggered();

    void on_Today_button_4_clicked();

    void on_calendar_button_4_clicked();

    void on_progress_button_4_clicked();

    void on_roadmap_button_clicked();

    void on_actionroadmap_triggered();

private:
    Ui::MainWindow *ui;
    Today_Acts *ptrTodayActs;
    Calendar_Acts *ptrCalendActs;
    ProgressFallWidget *ptrProgFall;
    Roadmaps *ptrRoadmaps;

};

#endif // MAINWINDOW_H
