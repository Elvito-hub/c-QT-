#ifndef PROGRESSFALLWIDGET_H
#define PROGRESSFALLWIDGET_H

#include <QWidget>
#include"linechart.h"

namespace Ui {
class ProgressFallWidget;
}

class ProgressFallWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProgressFallWidget(QWidget *parent = 0);
    QString getStartDate(QString date);

    LineChart *ptrLineChart;
    ~ProgressFallWidget();
public slots:
    void updateDiff();

private:
    Ui::ProgressFallWidget *ui;

};

#endif // PROGRESSFALLWIDGET_H
