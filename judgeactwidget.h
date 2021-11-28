#ifndef JUDGEACTWIDGET_H
#define JUDGEACTWIDGET_H

#include <QWidget>

namespace Ui {
class JudgeActWidget;
}

class JudgeActWidget : public QWidget
{
    Q_OBJECT

public:
    explicit JudgeActWidget(QWidget *parent = 0);
    Ui::JudgeActWidget *ui;
    ~JudgeActWidget();

private:

};

#endif // JUDGEACTWIDGET_H
