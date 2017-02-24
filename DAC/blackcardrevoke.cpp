#include "blackcardrevoke.h"
#include "ui_blackcardrevoke.h"
#include "database.h"

extern QString globalname;
BlackCardRevoke::BlackCardRevoke(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BlackCardRevoke)
{
    ui->setupUi(this);
    this->setWindowTitle("撤销黑令牌");
}

BlackCardRevoke::~BlackCardRevoke()
{
    delete ui;
}

void BlackCardRevoke::on_yesButton_clicked()
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
        QMessageBox::warning(this,"Warning","请输入撤销黑令牌的主体名称!",QMessageBox::Yes);
        ui->ObjName->clear();
        ui->UserName->clear();
        ui->checkBoxr->setChecked(false);
        ui->checkBoxw->setChecked(false);
        ui->checkBoxc->setChecked(false);
        ui->ObjName->setFocus();
        return;
    }
    if(ui->UserName->text() == globalname){
        QMessageBox::warning(this,"Warning","不能撤销自身黑令牌!",QMessageBox::Yes);
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

    if(!createConnection()){
        QMessageBox::warning(this,"Warning","无法连接到数据库!",QMessageBox::Yes);
        return;
    }
    QSqlQuery query,query2;
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
        QMessageBox::warning(this,"Warning","被撤销黑令牌的主体不存在!",QMessageBox::Yes);
        ui->ObjName->clear();
        ui->UserName->clear();
        ui->checkBoxr->setChecked(false);
        ui->checkBoxw->setChecked(false);
        ui->checkBoxc->setChecked(false);
        ui->ObjName->setFocus();
        return;
    }

    query.prepare("select * from Object where ObjID= ? and UserID= ? ");
    query.addBindValue(ui->ObjName->text());
    query.addBindValue(globalname);
    query.exec();
    query.next();
    if(query.isValid()){//拥有者
        if(ui->checkBoxr->isChecked()){//读黑令牌撤销
            query.prepare("select * from BlackList where UserID= ? and ObjID= ? and noAbility= ? and GiverID= ? ");
            query.addBindValue(ui->UserName->text());
            query.addBindValue(ui->ObjName->text());
            query.addBindValue("r");
            query.addBindValue(globalname);
            query.exec();
            query.next();
            if(!query.isValid()){
                QMessageBox::warning(this,"Warning","该黑令牌不存在!",QMessageBox::Yes);
            }
            else{
                query.prepare("delete from BlackList where UserID= ? and ObjID= ? and noAbility= ? and GiverID= ? ");
                query.addBindValue(ui->UserName->text());
                query.addBindValue(ui->ObjName->text());
                query.addBindValue("r");
                query.addBindValue(globalname);
                query.exec();
                //QMessageBox::warning(this,"Warning","1!",QMessageBox::Yes);
            }
        }
        if(ui->checkBoxw->isChecked()){//写黑令牌撤销
            query.prepare("select * from BlackList where UserID= ? and ObjID= ? and noAbility= ? and GiverID= ? ");
            query.addBindValue(ui->UserName->text());
            query.addBindValue(ui->ObjName->text());
            query.addBindValue("w");
            query.addBindValue(globalname);
            query.exec();
            query.next();
            if(!query.isValid()){
                QMessageBox::warning(this,"Warning","该黑令牌不存在!",QMessageBox::Yes);
            }
            else{
                query.prepare("delete from BlackList where UserID= ? and ObjID= ? and noAbility= ? and GiverID= ? ");
                query.addBindValue(ui->UserName->text());
                query.addBindValue(ui->ObjName->text());
                query.addBindValue("w");
                query.addBindValue(globalname);
                query.exec();
                //QMessageBox::warning(this,"Warning","2!",QMessageBox::Yes);

            }
        }
        if(ui->checkBoxc->isChecked()){//控制黑令牌撤销
            query.prepare("select * from BlackList where UserID= ? and ObjID= ? and noAbility= ? and GiverID= ? ");
            query.addBindValue(ui->UserName->text());
            query.addBindValue(ui->ObjName->text());
            query.addBindValue("c");
            query.addBindValue(globalname);
            query.exec();
            query.next();
            if(!query.isValid()){
                QMessageBox::warning(this,"Warning","该黑令牌不存在!",QMessageBox::Yes);
            }
            else{
                query.prepare("delete from BlackList where UserID= ? and ObjID= ? and noAbility= ? and GiverID= ? ");
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
        QMessageBox::warning(this,"Warning","无法撤销黑令牌，不是该客体的拥有者！",QMessageBox::Yes);
    }
    this->close();
}

void BlackCardRevoke::on_closeButton_clicked()
{
    this->close();
}

void BlackCardRevoke::on_checkBoxc_clicked(bool checked)
{
    //复选框设置
    //若撤销控制权黑令牌，则需要同时撤销已存在的读写黑令牌
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
        createConnection();
        QSqlQuery query;
        query.prepare("select * from BlackList where UserID= ? and ObjID= ? and noAbility= ? and GiverID= ? ");
        query.addBindValue(ui->UserName->text());
        query.addBindValue(ui->ObjName->text());
        query.addBindValue("r");
        query.addBindValue(globalname);
        query.exec();
        query.next();
        if(query.isValid() && !ui->checkBoxr->isChecked()){
            ui->checkBoxr->setChecked(true);
        }
        query.prepare("select * from BlackList where UserID= ? and ObjID= ? and noAbility= ? and GiverID= ? ");
        query.addBindValue(ui->UserName->text());
        query.addBindValue(ui->ObjName->text());
        query.addBindValue("w");
        query.addBindValue(globalname);
        query.exec();
        query.next();
        if(query.isValid() && !ui->checkBoxw->isChecked()){
            ui->checkBoxw->setChecked(true);
        }
    }
    else{
        ui->checkBoxw->setChecked(false);
        ui->checkBoxr->setChecked(false);
    }
}
