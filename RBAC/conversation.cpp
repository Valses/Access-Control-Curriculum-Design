#include "conversation.h"
#include "ui_conversation.h"
#include "database.h"

extern QString globalname;
QStringList rolelist; //已激活的所有角色和其子角色表

Conversation::Conversation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Conversation)
{
    ui->setupUi(this);
    this->setWindowTitle("创建会话");

    QSqlQuery query, query2;
    query.prepare("select * from ActiveU where User = ?");
    query.addBindValue(globalname);
    query.exec();
    //query.next();
    QString role, power;
    while(query.next()){
        role = query.value(2).toString();
        rolelist.append(role);
        query2.prepare("select * from PR where Role = ?");
        query2.addBindValue(role);
        query2.exec();
        while(query2.next()){
            power = query2.value(2).toString();
            powerlist1.append(power);
        }
        //检查角色层次表，添加继承权限
        addInPower(role);
    }
    qDebug() << powerlist1;
    qDebug() << powerlist2;
    QString str;
    for(int i = 0; i < powerlist1.length(); i++){
        str = str +  powerlist1[i] + " ";
    }
    ui->lineEdit->setText(str);
    ui->lineEdit->setEnabled(false);
    str = "";
    for(int i = 0; i < powerlist2.length(); i++){
        str = str + powerlist2[i] + " ";
    }
    ui->lineEdit_2->setText(str);
    ui->lineEdit_2->setEnabled(false);
}

void Conversation::addInPower(QString role){
    QSqlQuery query, query2;
    QString str, power;
    query.prepare("select * from RH where Role = ? ");
    query.addBindValue(role);
    query.exec();
    while (query.next()){
        str = query.value(2).toString();
        //取消对创建会话时子角色的互斥考虑
        /*
        if(isMutex(str)){
            qDebug() << "jihuohuchi";
            break;
        }
        */
        rolelist.append(str);
        qDebug() << "add";
        query2.prepare("select * from PR where Role = ?");
        query2.addBindValue(str);
        query2.exec();
        while(query2.next()){
            power = query2.value(2).toString();
            powerlist2.append(power);
        }
        addInPower(str);
    }

}

bool Conversation::isMutex(QString role){
    //创建会话的时候，查询已激活角色和子角色中有没有存在互斥
    //互斥则不授予相应权限
    QSqlQuery query, query2;
    QString arole;
    for(int i = 0; i < rolelist.length(); i++){
        arole = rolelist[i];
        //arole = query2.value(2).toString();
        qDebug() << role;
        qDebug() << arole;
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
}



Conversation::~Conversation()
{
    delete ui;
}
