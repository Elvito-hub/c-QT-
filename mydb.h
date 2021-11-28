#ifndef MYDB_H
#define MYDB_H

#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlQuery>
#include<QFile>
#include<QDebug>
#include<QtSql/QSqlError>
#include<QtSql/QSqlQueryModel>



class MyDB
{
private:
    MyDB();
    //An instance is a single and unique unit of a class.
    static MyDB *instance1;
    void init();
    QSqlDatabase db;
public:
    //Since instance is static in the getInstance method it will retain its value between multiple invocations.
    static MyDB* getInstance1();
    static void ResetInstance1();
    QSqlDatabase getDBInstance1();
    ~MyDB();
};

#endif // MYDB_H
