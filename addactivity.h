#ifndef ADDACTIVITY_H
#define ADDACTIVITY_H

#include <QDialog>
#include<QDebug>
#include<QPushButton>
#include"mydb.h"

namespace Ui {
class AddActivity;
}

class AddActivity : public QDialog
{
    Q_OBJECT

public:
    explicit AddActivity(QWidget *parent = 0);
    QPushButton *postbutton;
    ~AddActivity();
    void Show();

private slots:
    void on_pushButton_clicked();

private:
    Ui::AddActivity *ui;
    void resetElements();
};

#endif // ADDACTIVITY_H
