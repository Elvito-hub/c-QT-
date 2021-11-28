#ifndef ROADMAPS_H
#define ROADMAPS_H

#include <QWidget>
#include"addroadmap.h"
#include"mydbrm.h"
#include"roadmapdraw.h"


namespace Ui {
class Roadmaps;
}

class Roadmaps : public QWidget
{
    Q_OBJECT

public:
    explicit Roadmaps(QWidget *parent = 0);

    void showRmDraw(QString title);
    RoadmapDraw *ptrmdraw;

    ~Roadmaps();

private:
    AddRoadmap *ptraddrm =NULL;

    Ui::Roadmaps *ui;
private slots:
    void showAddrm();
    void updateRmUi();

};

#endif // ROADMAPS_H
