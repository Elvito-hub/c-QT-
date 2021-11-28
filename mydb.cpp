#include "mydb.h"

MyDB* MyDB::instance1 = nullptr;

MyDB::MyDB()
{
    init();
}
void MyDB::init()
{
    db = QSqlDatabase::addDatabase("QSQLITE", "first_connection");
    db.setDatabaseName("C:/Users/gasan/Documents/dailyPlanner/daily-planner--qt-procedure/database/mydb.db");
    if(!db.open())
        qDebug() << "not open";
    else
        qDebug() << "connected...";
}
MyDB *MyDB::getInstance1()
{
    if(instance1 == nullptr)
        instance1 = new MyDB();
    return instance1;
}
QSqlDatabase MyDB::getDBInstance1()
{
    return db;
}
void MyDB::ResetInstance1()
{
    delete instance1;
    instance1 = nullptr;
}
MyDB::~MyDB()
{
    db.close();
}
