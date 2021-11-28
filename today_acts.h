#ifndef TODAY_ACTS_H
#define TODAY_ACTS_H

#include <QWidget>
#include<QDialog>
#include<QLineEdit>
#include<QTableView>
#include<QPushButton>
#include<QLabel>

#include<addactivity.h>
#include "mydb.h"
#include"piechart.h"

#include"delegate.h"



namespace Ui {
class Today_Acts;
}

class Today_Acts : public QWidget
{
    Q_OBJECT

public:
    explicit Today_Acts(QWidget *parent = 0);
    ~Today_Acts();
    QTableView *table;
    QPushButton *button;
    PieChart *ptrPiechart;
    void updateStatusJudge(const QString name,const QString date);
    QSqlQueryModel* fetch(QDate date);

private:
    Ui::Today_Acts *ui;
    AddActivity *ptrAddActivity= NULL;
private slots:
    void updateUi();
    void showAddAct();

};

#endif // TODAY_ACTS_H
