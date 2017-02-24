#include "activaterole.h"
#include "ui_activaterole.h"
#include"conversation.h"
#include "database.h"
extern QString globalname;
extern QStringList rolelist;
ActivateRole::ActivateRole(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ActivateRole)
{
    ui->setupUi(this);
    this->setWindowTitle("激活角色");
}

ActivateRole::~ActivateRole()
{
    delete ui;
}

void ActivateRole::on_yesButton_clicked()
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
    query.prepare("select * from UR where User = ? and Role= ?  ");
    query.addBindValue(globalname);
    query.addBindValue(ui->lineEdit->text());
    query.exec();
    query.next();
    if(!query.isValid()){
        QMessageBox::warning(this,"Warning","角色不属于该用户!",QMessageBox::Yes);
        ui->lineEdit->clear();
        ui->lineEdit->setFocus();
        return;
    }
    query.prepare("select * from ActiveU where User = ? and Role= ?  ");
    query.addBindValue(globalname);
    query.addBindValue(ui->lineEdit->text());
    query.exec();
    query.next();
    if(query.isValid()){
        QMessageBox::warning(this,"Warning","角色已激活!",QMessageBox::Yes);
        ui->lineEdit->clear();
        ui->lineEdit->setFocus();
        return;
    }

    if(isMutex(ui->lineEdit->text())){
        QMessageBox::warning(this,"Warning","角色互斥，无法激活!",QMessageBox::Yes);
        ui->lineEdit->clear();
        ui->lineEdit->setFocus();
        return;
    }
    int num = 1;
    query.exec("select * from ActiveU");
    if(query.last()){
        num = query.value(0).toInt();
        num++;
    }
    query.prepare("insert into ActiveU (ID, User, Role) values(?,?,?)");
    query.addBindValue(num);
    query.addBindValue(globalname);
    query.addBindValue(ui->lineEdit->text());
    query.exec();
    qDebug() << "jihuoziji";

    //角色层次，激活下级
    //activateChildRole(ui->lineEdit->text());
    //更改为在激活会话的时候判断角色层次激活下级权限

    QMessageBox::warning(this,"Warning","角色激活成功!",QMessageBox::Yes);
    accept();
}

void ActivateRole::activateChildRole(QString role){
    QSqlQuery query, query2;
    QString str;
    int num;
    query.prepare("select * from RH where Role = ? ");
    query.addBindValue(role);
    query.exec();
    while (query.next()){
        str = query.value(2).toString();
        //激活子角色时不考虑互斥
        /*
        if(isMutex(str)){
            //QMessageBox::warning(this,"Warning","角色互斥，无法激活!",QMessageBox::Yes);
            qDebug() << "jihuohuchi";
            break;
        }
        */
        num = 1;
        query2.exec("select * from ActiveU");
        if(query2.last()){
            num=query2.value(0).toInt();
            num++;
        }
        query2.prepare("insert into ActiveU (ID, User, Role) values (?, ?, ?)");
        query2.addBindValue(num);
        query2.addBindValue(globalname);
        query2.addBindValue(str);
        query2.exec();
        //qDebug() << "jihuozijuese";
        activateChildRole(str);
    }
}


bool ActivateRole::isMutex(QString role){
    //激活角色的时候，查询此角色与已激活角色中有没有存在互斥
    //互斥不激活
    QSqlQuery query, query2;
    QString arole;

    query.prepare("select * from ActiveU where User = ?");
    query.addBindValue(globalname);
    query.exec();
    while(query.next()){
        arole = query.value(2).toString();
        query2.prepare("select * from Mutex where Role = ? and Role2 = ?");
        query2.addBindValue(arole);
        query2.addBindValue(role);
        query2.exec();
        query2.next();
        if(query2.isValid()){
            qDebug() << "true1";
            return true;
        }
        else{
            query2.prepare("select * from Mutex where Role = ? and Role2 = ?");
            query2.addBindValue(role);
            query2.addBindValue(arole);
            query2.exec();
            query2.next();
            if(query2.isValid()){
                qDebug() << "true2";
                return true;
            }
        }

    }
    return false;

    /*
    //激活角色的时候，查询此角色与已激活角色和它们的子角色中有没有存在互斥
    //互斥则不激活
    QSqlQuery query;
    QString arole;
    for(int i = 0; i < rolelist.length(); i++){
        arole = rolelist[i];
        //arole = query2.value(2).toString();
        qDebug() << role;
        qDebug() << arole;
        query.prepare("select * from Mutex where Role = ? and Role2 = ?");
        query.addBindValue(arole);
        query.addBindValue(role);
        query.exec();
        query.next();
        if(query.isValid()){
            qDebug() << "true1";
            return true;
        }
        else{
            query.prepare("select * from Mutex where Role = ? and Role2 = ?");
            query.addBindValue(role);
            query.addBindValue(arole);
            query.exec();
            query.next();
            if(query.isValid()){
                qDebug() << "true2";
                return true;
            }
        }
    }
    return false;
    */
}


void ActivateRole::on_closeButton_clicked()
{
    this->close();
}
