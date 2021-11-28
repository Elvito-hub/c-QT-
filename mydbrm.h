#ifndef MYDBRM_H
#define MYDBRM_H

#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlQuery>
#include<QFile>
#include<QDebug>
#include<QtSql/QSqlError>
#include<QtSql/QSqlQueryModel>

class Mydbrm
{
private:
    Mydbrm();
    //An instance is a single and unique unit of a class.
    static Mydbrm *instance;
    void init();
    QSqlDatabase db;
public:
    //Since instance is static in the getInstance method it will retain its value between multiple invocations.
    static Mydbrm* getInstance();
    static void ResetInstance();
    QSqlDatabase getDBInstance();
    ~Mydbrm();
};

#endif // MYDBRM_H
