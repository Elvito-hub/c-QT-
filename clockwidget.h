#ifndef CLOCKWIDGET_H
#define CLOCKWIDGET_H

#include <QWidget>

class ClockWidget : public QWidget
{
    Q_OBJECT
public:
    ClockWidget(QWidget *parent = nullptr);
protected:
    void paintEvent(QPaintEvent *);
};

#endif // CLOCKWIDGET_H
