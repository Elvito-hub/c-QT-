#ifndef ADDROADMAP_H
#define ADDROADMAP_H

#include<QDialog>
#include <QWidget>
#include<QPushButton>
#include"mydbrm.h"

namespace Ui {
class AddRoadmap;
}

class AddRoadmap : public QDialog
{
    Q_OBJECT

public:
    explicit AddRoadmap(QWidget *parent = 0);
    void resetElements();
    QPushButton *postbutton;
    ~AddRoadmap();

private slots:
    void on_pushButton_clicked();

private:
    Ui::AddRoadmap *ui;
};

#endif // ADDROADMAP_H
