#ifndef DATABASE_H
#define DATABASE_H
//数据库设置
#include <QSqlDatabase>
#include <QSqlQuery>

static bool isConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/Users/zyx1729/course/dacdb.db");
    if(!db.open())
        return false;
    QSqlQuery query;
    static int flag = 0;
    if(!flag){
        query.exec("create table User (UserID vchar primary key, passwd vchar, info vchar)");
        query.exec("create table Object (ObjID vchar primary key, UserID vchar)");
        query.exec("create table Power (No int primary key, UserID vchar, ObjID vchar, Ability vchar, GiverID vchar, Mark int, Del int)");
        query.exec("create table BlackList (No int primary key, UserID vcher, ObjID vchar, noAbility vchar, GiverID vchar)");
        flag++;
    }
    return true;
}
#endif // DATABASE_H
