#include "blackcardset.h"
#include "ui_blackcardset.h"
#include "database.h"

extern QString globalname;
BlackCardSet::BlackCardSet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BlackCardSet)
{
    ui->setupUi(this);
    this->setWindowTitle("创建黑令牌");
}

BlackCardSet::~BlackCardSet()
{
    delete ui;
}

void BlackCardSet::on_yesButton_clicked()
{


    if(ui->ObjName->text() == ""){
        QMessageBox::warning(this,"Warning","请输入客体名称!",QMessageBox::Yes);
        ui->ObjName->clear();
        ui->UserName->clear();
        ui->checkBoxr->setChecked(false);
        ui->checkBoxw->setChecked(false);
        ui->checkBoxc->setChecked(false);
        ui->ObjName->setFocus();
        return;
    }

    if(ui->UserName->text() == ""){
        QMessageBox::warning(this,"Warning","请输入被授予黑令牌的主体名称!",QMessageBox::Yes);
        ui->ObjName->clear();
        ui->UserName->clear();
        ui->checkBoxr->setChecked(false);
        ui->checkBoxw->setChecked(false);
        ui->checkBoxc->setChecked(false);
        ui->ObjName->setFocus();
        return;
    }
    if(ui->UserName->text() == globalname){
        QMessageBox::warning(this,"Warning","不能给自身添加黑令牌!",QMessageBox::Yes);
        ui->ObjName->clear();
        ui->UserName->clear();
        ui->checkBoxr->setChecked(false);
        ui->checkBoxw->setChecked(false);
        ui->checkBoxc->setChecked(false);
        ui->ObjName->setFocus();
        return;
    }

    if(!ui->checkBoxr->isChecked()&&!ui->checkBoxw->isChecked()&&!ui->checkBoxc->isChecked()){
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
    QSqlQuery query;
    query.prepare("select * from Object where ObjID= ? ");
    query.addBindValue(ui->ObjName->text());
    query.exec();
    query.next();
    if(!query.isValid()){
        QMessageBox::warning(this,"Warning","客体不存在!",QMessageBox::Yes);
        ui->ObjName->clear();
        ui->UserName->clear();
        ui->checkBoxr->setChecked(false);
        ui->checkBoxw->setChecked(false);
        ui->checkBoxc->setChecked(false);
        ui->ObjName->setFocus();
        return;
    }
    query.prepare("select * from User where UserID= ? ");
    query.addBindValue(ui->UserName->text());
    query.exec();
    query.next();
    if(!query.isValid()){
        QMessageBox::warning(this,"Warning","被授予黑令牌的主体不存在!",QMessageBox::Yes);
        ui->ObjName->clear();
        ui->UserName->clear();
        ui->checkBoxr->setChecked(false);
        ui->checkBoxw->setChecked(false);
        ui->checkBoxc->setChecked(false);
        ui->ObjName->setFocus();
        return;
    }

    int num;
    query.prepare("select * from Object where ObjID= ? and UserID= ? ");
    query.addBindValue(ui->ObjName->text());
    query.addBindValue(globalname);
    query.exec();
    query.next();
    if(query.isValid()){//拥有者
        if(ui->checkBoxr->isChecked()){//读黑令牌
            query.prepare("select * from BlackList where UserID= ? and ObjID= ? and noAbility= ? and GiverID= ? ");
            query.addBindValue(ui->UserName->text());
            query.addBindValue(ui->ObjName->text());
            query.addBindValue("r");
            query.addBindValue(globalname);
            query.exec();
            query.next();
            if(query.isValid()){
                QMessageBox::warning(this,"Warning","r:该黑令牌已存在!",QMessageBox::Yes);
            }
            else{
                num = 1;
                query.exec("select * from BlackList");
                if(query.last()){
                    num = query.value(0).toInt();
                    num++;
                }
                query.prepare("insert into BlackList (No, UserID, ObjID, noAbility, GiverID) values(?,?,?,?,?)");
                query.addBindValue(num);
                query.addBindValue(ui->UserName->text());
                query.addBindValue(ui->ObjName->text());
                query.addBindValue("r");
                query.addBindValue(globalname);
                query.exec();
                //QMessageBox::warning(this,"Warning","1!",QMessageBox::Yes);
            }
        }
        if(ui->checkBoxw->isChecked()){//写黑令牌
            query.prepare("select * from BlackList where UserID= ? and ObjID= ? and noAbility= ? and GiverID= ? ");
            query.addBindValue(ui->UserName->text());
            query.addBindValue(ui->ObjName->text());
            query.addBindValue("w");
            query.addBindValue(globalname);
            query.exec();
            query.next();
            if(query.isValid()){
                QMessageBox::warning(this,"Warning","w:该黑令牌已存在!",QMessageBox::Yes);
            }
            else{
                num = 1;
                query.exec("select * from BlackList");
                if(query.last()){
                    num = query.value(0).toInt();
                    num++;
                }
                query.prepare("insert into BlackList (No, UserID, ObjID, noAbility, GiverID) values(?,?,?,?,?)");
                query.addBindValue(num);
                query.addBindValue(ui->UserName->text());
                query.addBindValue(ui->ObjName->text());
                query.addBindValue("w");
                query.addBindValue(globalname);
                query.exec();
                //QMessageBox::warning(this,"Warning","2!",QMessageBox::Yes);

            }
        }
        if(ui->checkBoxc->isChecked()){//控制黑令牌
            query.prepare("select * from BlackList where UserID= ? and ObjID= ? and noAbility= ? and GiverID= ? ");
            query.addBindValue(ui->UserName->text());
            query.addBindValue(ui->ObjName->text());
            query.addBindValue("c");
            query.addBindValue(globalname);
            query.exec();
            query.next();
            if(query.isValid()){
                QMessageBox::warning(this,"Warning","c:该黑令牌已存在!",QMessageBox::Yes);
            }
            else{
                num = 1;
                query.exec("select * from BlackList");
                if(query.last()){
                    num = query.value(0).toInt();
                    num++;
                }
                query.prepare("insert into BlackList (No, UserID, ObjID, noAbility, GiverID) values(?, ?, ?, ?, ?)");
                query.addBindValue(num);
                query.addBindValue(ui->UserName->text());
                query.addBindValue(ui->ObjName->text());
                query.addBindValue("c");
                query.addBindValue(globalname);
                query.exec();
                //QMessageBox::warning(this,"Warning","3!",QMessageBox::Yes);

            }
        }
    }
    else{   //非拥有者
        QMessageBox::warning(this,"Warning","无法授予黑令牌，不是该客体的拥有者！",QMessageBox::Yes);
    }
    this->close();

}




void BlackCardSet::on_closeButton_clicked()
{
    this->close();
}

void BlackCardSet::on_checkBoxr_clicked(bool checked)
{
    //复选框设置
    //若添加读黑令牌，且控制黑令牌不存在，则同时添加控制黑令牌
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
        query.prepare("select * from BlackList where UserID= ? and ObjID= ? and noAbility= ? and GiverID= ? ");
        query.addBindValue(ui->UserName->text());
        query.addBindValue(ui->ObjName->text());
        query.addBindValue("c");
        query.addBindValue(globalname);
        query.exec();
        query.next();
        if(!query.isValid() && !ui->checkBoxc->isChecked()){
            ui->checkBoxc->setChecked(true);
        }
    }
    else{
        if(!ui->checkBoxw->isChecked())
            ui->checkBoxc->setChecked(false);
    }
}

void BlackCardSet::on_checkBoxw_clicked(bool checked)
{
    //复选框设置
    //若添加写黑令牌，且控制黑令牌不存在，则同时添加控制黑令牌
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
        query.prepare("select * from BlackList where UserID= ? and ObjID= ? and noAbility= ? and GiverID= ? ");
        query.addBindValue(ui->UserName->text());
        query.addBindValue(ui->ObjName->text());
        query.addBindValue("c");
        query.addBindValue(globalname);
        query.exec();
        query.next();
        if(!query.isValid() && !ui->checkBoxc->isChecked()){
            ui->checkBoxc->setChecked(true);
        }
    }
    else{
        if(!ui->checkBoxr->isChecked())
            ui->checkBoxc->setChecked(false);
    }
}
