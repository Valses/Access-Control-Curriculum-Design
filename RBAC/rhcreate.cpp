#include "rhcreate.h"
#include "ui_rhcreate.h"
#include "database.h"
RHCreate::RHCreate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RHCreate)
{
    ui->setupUi(this);
    this->setWindowTitle("角色层次创建");
}

RHCreate::~RHCreate()
{
    delete ui;
}

void RHCreate::on_yesButton_clicked()
{
    if(ui->role1Edit->text() == ""){
        QMessageBox::warning(this,"Warning","请输入父角色名称!",QMessageBox::Yes);
        ui->role1Edit->setFocus();
        return;
    }
    if(ui->role2Edit->text() == ""){
        QMessageBox::warning(this,"Warning","请输入子角色名称!",QMessageBox::Yes);
        ui->role2Edit->setFocus();
        return;
    }
    if(ui->role2Edit->text() == ui->role1Edit->text()){
        QMessageBox::warning(this,"Warning","请重新输入!",QMessageBox::Yes);
        ui->role1Edit->clear();
        ui->role2Edit->clear();
        ui->role1Edit->setFocus();
        return;
    }
    if(!isConnection()){
        QMessageBox::warning(this,"Warning","无法连接到数据库!",QMessageBox::Yes);
        return;
    }
    QSqlQuery query, query2;
    query.prepare("select * from Role where Role = ? ");
    query.addBindValue(ui->role1Edit->text());
    query.exec();
    query.next();
    if(!query.isValid())
    {
        QMessageBox::warning(this,"Warning","父角色不存在!",QMessageBox::Yes);
        ui->role1Edit->clear();
        ui->role2Edit->clear();
        ui->role1Edit->setFocus();
        return;
    }
    query.prepare("select * from Role where Role = ? ");
    query.addBindValue(ui->role2Edit->text());
    query.exec();
    query.next();
    if(!query.isValid())
    {
        QMessageBox::warning(this,"Warning","子角色不存在!",QMessageBox::Yes);
        ui->role2Edit->clear();
        ui->role2Edit->setFocus();
        return;
    }
    query.prepare("select * from Mutex where Role = ? and Role2 = ?");
    query.addBindValue(ui->role1Edit->text());
    query.addBindValue(ui->role2Edit->text());
    query.exec();
    query.next();
    if(query.isValid()){
        QMessageBox::warning(this,tr("Warning"),tr("huchi!"),QMessageBox::Yes);
        ui->role1Edit->clear();
        ui->role2Edit->clear();
        ui->role1Edit->setFocus();
        return;
    }

    //互斥关系
    query.prepare("select * from Mutex where Role = ? and Role2 = ?");
    query.addBindValue(ui->role2Edit->text());
    query.addBindValue(ui->role1Edit->text());
    query.exec();
    query.next();
    if(query.isValid()){
        QMessageBox::warning(this,tr("Warning"),tr("互斥!"),QMessageBox::Yes);
        ui->role1Edit->clear();
        ui->role2Edit->clear();
        ui->role1Edit->setFocus();
        return;
    }

    query.prepare("select * from RH where Role = ? and Child = ?");
    query.addBindValue(ui->role1Edit->text());
    query.addBindValue(ui->role2Edit->text());
    query.exec();
    query.next();
    if(query.isValid()){
        QMessageBox::warning(this,tr("Warning"),tr("角色层次已存在!"),QMessageBox::Yes);
        ui->role1Edit->clear();
        ui->role2Edit->clear();
        ui->role1Edit->setFocus();
        return;
    }

    if(findLoop(ui->role1Edit->text(), ui->role2Edit->text()))
    {
        QMessageBox::warning(this,tr("Warning"),tr("循环!"),QMessageBox::Yes);
        ui->role1Edit->clear();
        ui->role2Edit->clear();
        ui->role1Edit->setFocus();
        return;
    }
    int num = 1;
    query.exec("select * from RH");
    if(query.last()){
        num=query.value(0).toInt();
        num++;
    }
    query.prepare("insert into RH (ID, Role, Child) values (?, ?, ?)");
    query.addBindValue(num);
    query.addBindValue(ui->role1Edit->text());
    query.addBindValue(ui->role2Edit->text());
    query.exec();
    //addRHList(ui->role1Edit->text(), ui->role2Edit->text());
    //取消了所有的父角色继承
    QMessageBox::warning(this,tr("Congratulations"),tr("角色层次添加成功!"),QMessageBox::Yes);
    accept();

}

bool RHCreate::findLoop(QString fa, QString cd){
    QSqlQuery query;
    QString str;
    int flag = 0;
    query.prepare("select * from RH where Child = ? ");
    query.addBindValue(fa);
    query.exec();
    while (query.next()){
        str = query.value(1).toString();
        if (str == cd){
            flag = 1;
            break;
        }
        else{
            flag = findLoop(str, cd);
            if(flag)
                break;
        }
    }
    return flag;
}

void RHCreate::addRHList(QString fa, QString cd){
    QSqlQuery query;
    QString str;
    int num;
    //int flag = 0;
    query.prepare("select * from RH where Child = ? ");
    query.addBindValue(fa);
    query.exec();
    while (query.next()){
        str = query.value(1).toString();
        num = 1;
        query.exec("select * from RH");
        if(query.last()){
            num=query.value(0).toInt();
            num++;
        }
        query.prepare("insert into RH (ID, Role, Child) values (?, ?, ?)");
        query.addBindValue(num);
        query.addBindValue(str);
        query.addBindValue(cd);
        query.exec();
        addRHList(str, cd);
    }
}

void RHCreate::on_closeButton_clicked()
{
    this->close();
}
