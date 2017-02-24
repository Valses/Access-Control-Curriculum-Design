#ifndef DATABASE_H
#define DATABASE_H


#include <QSqlDatabase>
#include <QSqlQuery>

static bool isConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/Users/zyx1729/course/rbac4.db");
    if(!db.open()) return false;
    QSqlQuery query;
    query.exec("create table User (UserID vchar primary key, Passwd char)");
    query.exec("create table Role (Role vchar primary key)");
    query.exec("create table Power (Power vchar primary key)");

    query.exec("create table UR (ID int primary key , User vchar , Role vchar)");
    query.exec("create table PR (ID int primary key , Role vchar , Power vchar)");
    query.exec("create table RHF (ID int primary key , Role vchar , Father vchar)");
    query.exec("create table RH (ID int primary key , Role vchar , Child vchar)");

    query.exec("create table Mutex (ID int primary key , Role vchar , Role2 vchar)");

    query.exec("create table ActiveU (ID int primary key , User vchar , Role vchar)");
    return true;

}

#endif // DATABASE_H
