#include "mydbrm.h"

Mydbrm* Mydbrm::instance = nullptr;
Mydbrm::Mydbrm()
{
    init();
}

void Mydbrm::init()
{
    db = QSqlDatabase::addDatabase("QSQLITE","second_connection");
    db.setDatabaseName("C:/Users/gasan/Documents/dailyPlanner/daily-planner--qt-procedure/database/mydbrm.db");
    if(!db.open())
        qDebug()<<"Not open";
    else
        qDebug()<<"connected...";
}
Mydbrm *Mydbrm::getInstance()
{
    if(instance == nullptr)
        instance = new Mydbrm();
    return instance;
}
QSqlDatabase Mydbrm::getDBInstance()
{
    return db;
}
void Mydbrm::ResetInstance()
{
    delete instance;
    instance = nullptr;
}

Mydbrm::~Mydbrm()
{
    db.close();
}
