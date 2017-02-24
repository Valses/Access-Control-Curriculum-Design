#include "roledelete.h"
#include "ui_roledelete.h"
#include "database.h"
RoleDelete::RoleDelete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RoleDelete)
{
    ui->setupUi(this);
    this->setWindowTitle("删除角色");
}

RoleDelete::~RoleDelete()
{
    delete ui;
}

void RoleDelete::on_yesButton_clicked()
{
    if(ui->lineEdit->text() == ""){
        QMessageBox::warning(this,"Warning","请输入角色名称!",QMessageBox::Yes);
        ui->lineEdit->setFocus();
        return;
    }
    if(!isConnection()){
        QMessageBox::warning(this,"Warning","无法连接到数据库!",QMessageBox::Yes);
        return;
    }
    QSqlQuery query;
    query.prepare("select * from Role where Role= ? ");
    query.addBindValue(ui->lineEdit->text());
    query.exec();
    query.next();
    if(!query.isValid()){
        QMessageBox::warning(this,"Warning","角色不存在!",QMessageBox::Yes);
        ui->lineEdit->clear();
        ui->lineEdit->setFocus();
        return;
    }

    query.prepare("delete from Role where Role = ?");
    query.addBindValue(ui->lineEdit->text());
    query.exec();
    qDebug() << "1";
    query.prepare("delete from PR where Role = ?");
    query.addBindValue(ui->lineEdit->text());
    query.exec();
    qDebug() << "2";
    query.prepare("delete from UR where Role = ?");
    query.addBindValue(ui->lineEdit->text());
    query.exec();
    qDebug() << "3";
    query.prepare("delete from Mutex where Role = ?");
    query.addBindValue(ui->lineEdit->text());
    query.exec();
    qDebug() << "4";
    query.prepare("delete from Mutex where Role2 = ?");
    query.addBindValue(ui->lineEdit->text());
    query.exec();
    qDebug() << "5";
    query.prepare("delete from ActiveU where Role = ?");
    query.addBindValue(ui->lineEdit->text());
    query.exec();

    QStringList rolelist1, rolelist2;
    int num;
    //考虑角色层次关系
    query.prepare("select * from RH where Role = ?");
    query.addBindValue(ui->lineEdit->text());
    query.exec();
    while(query.next()){
        rolelist1.append(query.value(2).toString());
    }
    query.prepare("select * from RH where Child = ?");
    query.addBindValue(ui->lineEdit->text());
    query.exec();
    while(query.next()){
        rolelist2.append(query.value(1).toString());
    }
    for(int i = 0; i < rolelist1.length(); i++){
        for(int j = 0; j < rolelist2.length(); j++){
            num = 1;
            query.exec("select * from RH");
            if(query.last()){
                num = query.value(0).toInt();
                num++;
            }
            query.prepare("insert into RH (ID, Role, Child) values(?, ?, ?)");
            query.addBindValue(num);
            query.addBindValue(rolelist2[j]);
            query.addBindValue(rolelist1[i]);
            query.exec();
        }
    }
    query.prepare("delete from RH where Role = ?");
    query.addBindValue(ui->lineEdit->text());
    query.exec();
    query.prepare("delete from RH where Child = ?");
    query.addBindValue(ui->lineEdit->text());
    query.exec();

    QMessageBox::warning(this,"Congratulations","角色已删除!",QMessageBox::Yes);
    accept();
}

void RoleDelete::on_closeButton_clicked()
{
    this->close();
}
