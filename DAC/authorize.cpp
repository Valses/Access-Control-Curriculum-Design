#include "authorize.h"
#include "ui_authorize.h"
#include "database.h"

extern QString globalname;

Authorize::Authorize(QWidget *parent) :
QDialog(parent),
ui(new Ui::Authorize)
{
    ui->setupUi(this);
    this->setWindowTitle("授权");
}

Authorize::~Authorize()
{
    delete ui;
}

void Authorize::on_yesButton_clicked()
{
    int num, del = 0, mark = 0;
    int parent, sparent;
    if(ui->ObjName->text() == "")
    {
        QMessageBox::warning(this,"Warning","请输入客体名称!",QMessageBox::Yes);
        ui->ObjName->clear();
        ui->UserName->clear();
        ui->checkBoxr->setChecked(false);
        ui->checkBoxw->setChecked(false);
        ui->checkBoxc->setChecked(false);
        ui->ObjName->setFocus();
        return;
    }
    if(ui->UserName->text() == "")
    {
        QMessageBox::warning(this,"Warning","请输入被授权的主体名称!",QMessageBox::Yes);
        ui->ObjName->clear();
        ui->UserName->clear();
        ui->checkBoxr->setChecked(false);
        ui->checkBoxw->setChecked(false);
        ui->checkBoxc->setChecked(false);
        ui->ObjName->setFocus();
        return;
    }
    if(ui->UserName->text() == globalname)
    {
        QMessageBox::warning(this,"Warning","不能给自身授权!",QMessageBox::Yes);
        ui->ObjName->clear();
        ui->UserName->clear();
        ui->checkBoxr->setChecked(false);
        ui->checkBoxw->setChecked(false);
        ui->checkBoxc->setChecked(false);
        ui->ObjName->setFocus();
        return;
    }
    if(!ui->checkBoxr->isChecked()&&!ui->checkBoxw->isChecked()&&!ui->checkBoxc->isChecked())
    {
        QMessageBox::warning(this,"Warning","至少选择一种权限!",QMessageBox::Yes);
        ui->ObjName->clear();
        ui->UserName->clear();
        ui->checkBoxr->setChecked(false);
        ui->checkBoxw->setChecked(false);
        ui->checkBoxc->setChecked(false);
        ui->ObjName->setFocus();
        return;
    }
    if(!isConnection()){
        QMessageBox::warning(this,"Warning","无法连接到数据库!",QMessageBox::Yes);
        return;
    }
    QSqlQuery query,query2;

    query.prepare("select * from User where UserID= ? ");
    query.addBindValue(ui->UserName->text());
    query.exec();
    query.next();
    if(!query.isValid())
    {
        QMessageBox::warning(this,"Warning","被授权主体不存在!",QMessageBox::Yes);
        ui->ObjName->clear();
        ui->UserName->clear();
        ui->checkBoxr->setChecked(false);
        ui->checkBoxw->setChecked(false);
        ui->checkBoxc->setChecked(false);
        ui->ObjName->setFocus();
        return;
    }
    query.prepare("select * from Object where ObjID= ? ");
    query.addBindValue(ui->ObjName->text());
    query.exec();
    query.next();
    if(!query.isValid())
    {
        QMessageBox::warning(this,"Warning","客体不存在!",QMessageBox::Yes);
        ui->ObjName->clear();
        ui->UserName->clear();
        ui->checkBoxr->setChecked(false);
        ui->checkBoxw->setChecked(false);
        ui->checkBoxc->setChecked(false);
        ui->ObjName->setFocus();
        return;
    }



    //判断是否具有o权或者c权
    query.prepare("select * from Power where UserID= ? and ObjID= ? and Ability= ?");
    query.addBindValue(globalname);
    query.addBindValue(ui->ObjName->text());
    query.addBindValue("o");
    query.exec();
    query.next();
    if(query.isValid()){ //拥有者授权
        mark = query.value(0).toInt();
        if(ui->checkBoxr->isChecked()){ //读权已选择
            query.prepare("select * from BlackList where UserID= ? and ObjID= ? and noAbility= ? ");
            query.addBindValue(ui->UserName->text());
            query.addBindValue(ui->ObjName->text());
            query.addBindValue("r");
            query.exec();
            query.next();
            if(query.isValid()){
                QMessageBox::warning(this,"Warning","r:无法授权，黑令牌限制!",QMessageBox::Yes);
            }
            else{
                query.prepare("select * from Power where UserID= ? and ObjID= ? and Ability= ? and GiverID= ?");
                query.addBindValue(ui->UserName->text());
                query.addBindValue(ui->ObjName->text());
                query.addBindValue("r");
                query.addBindValue(globalname);
                query.exec();
                query.next();
                if(query.isValid()){
                    QMessageBox::warning(this,"Warning","r:此授权已存在!",QMessageBox::Yes);
                }
                else{
                    num = 1;
                    query.exec("select * from Power");
                    if(query.last()){
                        num = query.value(0).toInt();
                        num++;
                    }
                    query.prepare("insert into Power (No, UserID, ObjID, Ability, GiverID, Mark,Del) values(?, ?, ?, ?, ?, ?, ?)");
                    query.addBindValue(num);
                    query.addBindValue(ui->UserName->text());
                    query.addBindValue(ui->ObjName->text());
                    query.addBindValue("r");
                    query.addBindValue(globalname);
                    query.addBindValue(mark);
                    query.addBindValue(del);
                    query.exec();
                    //QMessageBox::warning(this,"Warning","r:授权成功!",QMessageBox::Yes);
                }
            }

        }
        if(ui->checkBoxw->isChecked()){ //写权已选择
            query.prepare("select * from BlackList where UserID= ? and ObjID= ? and noAbility= ? ");
            query.addBindValue(ui->UserName->text());
            query.addBindValue(ui->ObjName->text());
            query.addBindValue("w");
            query.exec();
            query.next();
            if(query.isValid()){
                QMessageBox::warning(this,"Warning","w:无法授权，黑令牌限制!",QMessageBox::Yes);
            }
            else{
                query.prepare("select * from Power where UserID= ? and ObjID= ? and Ability= ? and GiverID= ?");
                query.addBindValue(ui->UserName->text());
                query.addBindValue(ui->ObjName->text());
                query.addBindValue("w");
                query.addBindValue(globalname);
                query.exec();
                query.next();
                if(query.isValid()){
                    QMessageBox::warning(this,"Warning","w:此授权已存在!",QMessageBox::Yes);
                }
                else{
                    num = 1;
                    query.exec("select * from Power");
                    if(query.last()){
                        num = query.value(0).toInt();
                        num++;
                    }
                    query.prepare("insert into Power (No, UserID, ObjID, Ability, GiverID, Mark, Del) values(?, ?, ?, ?, ?, ?, ?)");
                    query.addBindValue(num);
                    query.addBindValue(ui->UserName->text());
                    query.addBindValue(ui->ObjName->text());
                    query.addBindValue("w");
                    query.addBindValue(globalname);
                    query.addBindValue(mark);
                    query.addBindValue(del);
                    query.exec();
                    //QMessageBox::warning(this,"Warning","w:授权成功!",QMessageBox::Yes);
                }
            }
        }
        if(ui->checkBoxc->isChecked()){ //控制权已选择
            query.prepare("select * from BlackList where UserID= ? and ObjID= ? and noAbility= ? ");
            query.addBindValue(ui->UserName->text());
            query.addBindValue(ui->ObjName->text());
            query.addBindValue("c");
            query.exec();
            query.next();
            if(query.isValid()){
                QMessageBox::warning(this,"Warning","c:无法授权，黑令牌限制!",QMessageBox::Yes);
            }
            else{
                query.prepare("select * from Power where UserID= ? and ObjID= ? and Ability= ? and GiverID= ?");
                query.addBindValue(ui->UserName->text());
                query.addBindValue(ui->ObjName->text());
                query.addBindValue("c");
                query.addBindValue(globalname);
                query.exec();
                query.next();
                if(query.isValid()){
                    QMessageBox::warning(this,"Warning","c:此授权已存在!",QMessageBox::Yes);
                }
                else{
                    num = 1;
                    query.exec("select * from Power");
                    if(query.last()){
                        num = query.value(0).toInt();
                        num++;
                    }
                    query.prepare("insert into Power (No, UserID, ObjID, Ability, GiverID, Mark, Del) values(?, ?, ?, ?, ?, ?, ?)");
                    query.addBindValue(num);
                    query.addBindValue(ui->UserName->text());
                    query.addBindValue(ui->ObjName->text());
                    query.addBindValue("c");
                    query.addBindValue(globalname);
                    query.addBindValue(mark);
                    query.addBindValue(del);
                    query.exec();
                    //QMessageBox::warning(this,"Warning","c:授权成功!",QMessageBox::Yes);
                }
            }
        }
    }
    else{
        query.prepare("select * from Power where UserID= ? and ObjID= ? and Ability= ? ");
        query.addBindValue(globalname);
        query.addBindValue(ui->ObjName->text());
        query.addBindValue("c");
        query.exec();
        query.next();
        if(query.isValid()){ //有控制权者授权
            sparent = query.value(5).toInt();
            mark = query.value(0).toInt();

            query.prepare("select * from BlackList where UserID= ? and ObjID= ? and noAbility= ? ");
            query.addBindValue(globalname);
            query.addBindValue(ui->ObjName->text());
            query.addBindValue("c");
            query.exec();
            query.next();
            if(query.isValid()){
                QMessageBox::warning(this,"Warning","无法授权，控制权被黑令牌限制!",QMessageBox::Yes);
            }
            else{
                if(ui->checkBoxr->isChecked()){ //读权已选择
                    query.prepare("select * from BlackList where UserID= ? and ObjID= ? and noAbility= ? ");
                    query.addBindValue(ui->UserName->text());
                    query.addBindValue(ui->ObjName->text());
                    query.addBindValue("r");
                    query.exec();
                    query.next();
                    if(query.isValid()){
                        QMessageBox::warning(this,"Warning","r:无法授权，黑令牌限制!",QMessageBox::Yes);
                    }
                    else{
                        query.prepare("select * from Power where UserID= ? and ObjID= ? and Ability= ? and GiverID= ?");
                        query.addBindValue(ui->UserName->text());
                        query.addBindValue(ui->ObjName->text());
                        query.addBindValue("r");
                        query.addBindValue(globalname);
                        query.exec();
                        query.next();
                        if(query.isValid()){
                            QMessageBox::warning(this,"Warning","r:此授权已存在!",QMessageBox::Yes);
                        }
                        else{
                            parent = sparent;
                            while(1){
                                if(!parent){
                                    break;
                                }
                                else{
                                    query2.prepare("select * from Power where No = ?");
                                    query2.addBindValue(parent);
                                    query2.exec();
                                    query2.next();
                                    if(ui->UserName->text() == query2.value(1).toString()){
                                        break;
                                    }
                                    else{
                                        parent = query2.value(5).toInt();
                                    }
                                }
                            }
                            if(parent){
                                QMessageBox::warning(this,"Warning","r:授权失败，循环授权!",QMessageBox::Yes);
                            }
                            else{
                                num = 1;
                                query.exec("select * from Power");
                                if(query.last())
                                {
                                    num=query.value(0).toInt();
                                    num++;
                                }
                                query.prepare("insert into Power (No, UserID, ObjID, Ability, GiverID, Mark, Del) values (?, ?, ?, ?, ?, ?, ?)");
                                query.addBindValue(num);
                                query.addBindValue(ui->UserName->text());
                                query.addBindValue(ui->ObjName->text());
                                query.addBindValue("r");
                                query.addBindValue(globalname);
                                query.addBindValue(mark);
                                query.addBindValue(del);
                                query.exec();
                                //QMessageBox::warning(this,"Warning","r:授权成功!",QMessageBox::Yes);

                            }
                        }
                    }
                }
                if(ui->checkBoxw->isChecked()){ //写权已选择
                    query.prepare("select * from BlackList where UserID= ? and ObjID= ? and noAbility= ? ");
                    query.addBindValue(ui->UserName->text());
                    query.addBindValue(ui->ObjName->text());
                    query.addBindValue("w");
                    query.exec();
                    query.next();
                    if(query.isValid()){
                        QMessageBox::warning(this,"Warning","w:无法授权，黑令牌限制!",QMessageBox::Yes);
                    }
                    else{
                        query.prepare("select * from Power where UserID= ? and ObjID= ? and Ability= ? and GiverID= ?");
                        query.addBindValue(ui->UserName->text());
                        query.addBindValue(ui->ObjName->text());
                        query.addBindValue("w");
                        query.addBindValue(globalname);
                        query.exec();
                        query.next();
                        if(query.isValid()){
                            QMessageBox::warning(this,"Warning","w:此授权已存在!",QMessageBox::Yes);
                        }
                        else{
                            parent = sparent;
                            while(1){
                                if(!parent){
                                    break;
                                }
                                else{
                                    query2.prepare("select * from Power where No = ?");
                                    query2.addBindValue(parent);
                                    query2.exec();
                                    query2.next();
                                    if(ui->UserName->text() == query2.value(1).toString()){
                                        break;
                                    }
                                    else{
                                        parent = query2.value(5).toInt();
                                    }
                                }
                            }
                            if(parent){
                                QMessageBox::warning(this,"Warning","w:授权失败，循环授权!",QMessageBox::Yes);
                            }
                            else{
                                num = 1;
                                query.exec("select * from Power");
                                if(query.last())
                                {
                                    num=query.value(0).toInt();
                                    num++;
                                }
                                query.prepare("insert into Power (No, UserID, ObjID, Ability, GiverID, Mark, Del) values (?, ?, ?, ?, ?, ?, ?)");
                                query.addBindValue(num);
                                query.addBindValue(ui->UserName->text());
                                query.addBindValue(ui->ObjName->text());
                                query.addBindValue("w");
                                query.addBindValue(globalname);
                                query.addBindValue(mark);
                                query.addBindValue(del);
                                query.exec();
                                //QMessageBox::warning(this,"Warning","w:授权成功!",QMessageBox::Yes);

                            }
                        }

                    }
                }
                if(ui->checkBoxc->isChecked()){ //控制权已选择
                    query.prepare("select * from BlackList where UserID= ? and ObjID= ? and noAbility= ? ");
                    query.addBindValue(ui->UserName->text());
                    query.addBindValue(ui->ObjName->text());
                    query.addBindValue("c");
                    query.exec();
                    query.next();
                    if(query.isValid()){
                        QMessageBox::warning(this,"Warning","c:无法授权，黑令牌限制!",QMessageBox::Yes);
                    }
                    else{
                        query.prepare("select * from Power where UserID= ? and ObjID= ? and Ability= ? and GiverID= ?");
                        query.addBindValue(ui->UserName->text());
                        query.addBindValue(ui->ObjName->text());
                        query.addBindValue("c");
                        query.addBindValue(globalname);
                        query.exec();
                        query.next();
                        if(query.isValid()){
                            QMessageBox::warning(this,"Warning","c:此授权已存在!",QMessageBox::Yes);
                        }
                        else{
                            parent = sparent;
                            while(1){
                                if(!parent){
                                    break;
                                }
                                else{
                                    query2.prepare("select * from Power where No = ?");
                                    query2.addBindValue(parent);
                                    query2.exec();
                                    query2.next();
                                    if(ui->UserName->text() == query2.value(1).toString()){
                                        break;
                                    }
                                    else{
                                        parent = query2.value(5).toInt();
                                    }
                                }
                            }
                            if(parent){
                                QMessageBox::warning(this,"Warning","c:授权失败，循环授权!",QMessageBox::Yes);
                            }
                            else{
                                num = 1;
                                query.exec("select * from Power");
                                if(query.last())
                                {
                                    num=query.value(0).toInt();
                                    num++;
                                }
                                query.prepare("insert into Power (No, UserID, ObjID, Ability, GiverID, Mark, Del) values (?, ?, ?, ?, ?, ?, ?)");
                                query.addBindValue(num);
                                query.addBindValue(ui->UserName->text());
                                query.addBindValue(ui->ObjName->text());
                                query.addBindValue("c");
                                query.addBindValue(globalname);
                                query.addBindValue(mark);
                                query.addBindValue(del);
                                query.exec();
                                //QMessageBox::warning(this,"Warning","c:授权成功!",QMessageBox::Yes);

                            }
                        }
                    }
                }
            }
        }
        else{
            //无法授权
            QMessageBox::warning(this,"Warning","无法授权，不具备授权能力!",QMessageBox::Yes);
        }
    }
    this->close();
}


void Authorize::on_closeButton_clicked()
{
    this->close();
}


void Authorize::on_checkBoxc_clicked(bool checked)
{
    //复选框设置
    //如果选择授予控制权，则应该同时授予读写权
    if(ui->ObjName->text() == ""){
        QMessageBox::warning(this,"Warning","请输入客体名称!",QMessageBox::Yes);
        ui->ObjName->clear();
        ui->checkBoxr->setChecked(false);
        ui->checkBoxw->setChecked(false);
        ui->checkBoxc->setChecked(false);
        ui->ObjName->setFocus();
        return;
    }
    if(ui->UserName->text() == ""){
        QMessageBox::warning(this,"Warning","请输入主体名称!",QMessageBox::Yes);
        ui->UserName->clear();
        ui->checkBoxr->setChecked(false);
        ui->checkBoxw->setChecked(false);
        ui->checkBoxc->setChecked(false);
        ui->ObjName->setFocus();
        return;
    }
    if(checked){
        isConnection();
        QSqlQuery query;
        query.prepare("select * from Power where UserID= ? and ObjID= ? and Ability= ? and GiverID= ? ");
        query.addBindValue(ui->UserName->text());
        query.addBindValue(ui->ObjName->text());
        query.addBindValue("r");
        query.addBindValue(globalname);
        query.exec();
        query.next();
        if(!query.isValid() && !ui->checkBoxr->isChecked())
        {
            ui->checkBoxr->setChecked(true);
        }
        query.prepare("select * from Power where UserID= ? and ObjID= ? and Ability= ? and GiverID= ? ");
        query.addBindValue(ui->UserName->text());
        query.addBindValue(ui->ObjName->text());
        query.addBindValue("w");
        query.addBindValue(globalname);
        query.exec();
        query.next();
        if(!query.isValid() && !ui->checkBoxw->isChecked())
        {
            ui->checkBoxw->setChecked(true);
        }
    }
    else{
        ui->checkBoxw->setChecked(false);
        ui->checkBoxr->setChecked(false);
    }

}
