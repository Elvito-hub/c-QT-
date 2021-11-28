#include "judgeactwidget.h"
#include "ui_judgeactwidget.h"

JudgeActWidget::JudgeActWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JudgeActWidget)
{
    ui->setupUi(this);
    this->setMinimumSize(500,500);
    ui->line->setMinimumWidth(1000);
}

JudgeActWidget::~JudgeActWidget()
{
    delete ui;
}
