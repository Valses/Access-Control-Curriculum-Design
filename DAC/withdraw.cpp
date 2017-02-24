#include "withdraw.h"
#include "ui_withdraw.h"
#include "database.h"

extern QString globalname;

Withdraw::Withdraw(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Withdraw)
{
    ui->setupUi(this);
    this->setWindowTitle("撤销授权");
}

Withdraw::~Withdraw()
{
    delete ui;
}

void Withdraw::on_yesButton_clicked()
{
    if(ui->ObjName->text() == "")
    {
        QMessageBox::warning(this,tr("Warning"),tr("请输入客体名称!"),QMessageBox::Yes);
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
        QMessageBox::warning(this,"Warning","请输入被撤销权限的主体名称!",QMessageBox::Yes);
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
        QMessageBox::warning(this,"Warning","不能撤销自身权限!",QMessageBox::Yes);
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
    QSqlQuery query, query2;
    int parent, stop, del;
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
    query.prepare("select * from User where UserID= ? ");
    query.addBindValue(ui->UserName->text());
    query.exec();
    query.next();
    if(!query.isValid())
    {
        QMessageBox::warning(this,"Warning","被撤销授权的主体不存在!",QMessageBox::Yes);
        ui->ObjName->clear();
        ui->UserName->clear();
        ui->checkBoxr->setChecked(false);
        ui->checkBoxw->setChecked(false);
        ui->checkBoxc->setChecked(false);
        ui->ObjName->setFocus();
        return;
    }

    query.prepare("select * from Power where UserID= ? and ObjID= ? and Ability= ? ");
    query.addBindValue(globalname);
    query.addBindValue(ui->ObjName->text());
    query.addBindValue("o");
    query.exec();
    query.next();
    if(query.isValid()) //拥有者撤销授权
    {
        if(ui->checkBoxr->isChecked()){
            query.prepare("select * from Power where UserID= ? and ObjID= ? and Ability= ?");
            query.addBindValue(ui->UserName->text());
            query.addBindValue(ui->ObjName->text());
            query.addBindValue("r");
            query.exec();
            query.next();
            if(!query.isValid()){
                QMessageBox::warning(this,tr("Warning"),tr("r:此授权不存在!"),QMessageBox::Yes);
            }
            else
            {
                query.prepare("delete from Power where UserID= ? and ObjID= ? and Ability= ?");
                query.addBindValue(ui->UserName->text());
                query.addBindValue(ui->ObjName->text());
                query.addBindValue("r");
                query.exec();
            }
        }
        if(ui->checkBoxw->isChecked()){
            query.prepare("select * from Power where UserID= ? and ObjID= ? and Ability= ?");
            query.addBindValue(ui->UserName->text());
            query.addBindValue(ui->ObjName->text());
            query.addBindValue("w");
            query.exec();
            query.next();
            if(!query.isValid()){
                QMessageBox::warning(this,tr("Warning"),tr("w:此授权不存在!"),QMessageBox::Yes);
            }
            else
            {
                query.prepare("delete from Power where UserID= ? and ObjID= ? and Ability= ?");
                query.addBindValue(ui->UserName->text());
                query.addBindValue(ui->ObjName->text());
                query.addBindValue("w");
                //query.addBindValue(globalname);
                query.exec();

            }
        }
        if(ui->checkBoxc->isChecked()){
            query.prepare("select * from Power where UserID= ? and ObjID= ? and Ability= ?");
            query.addBindValue(ui->UserName->text());
            query.addBindValue(ui->ObjName->text());
            query.addBindValue("c");
            query.exec();
            query.next();
            if(!query.isValid()){
                QMessageBox::warning(this,"Warning","c:此授权不存在!",QMessageBox::Yes);
            }
            else{
                query.prepare("delete from Power where UserID= ? and ObjID= ? and Ability= ?");
                query.addBindValue(ui->UserName->text());
                query.addBindValue(ui->ObjName->text());
                query.addBindValue("c");
                //query.addBindValue(globalname);
                query.exec();
                while(1){
                    del = 1;
                    stop = 1;
                    query.exec("select * from Power");
                    while(query.next()){
                        parent = query.value(5).toInt();
                        query2.prepare("select * from Power where No=?");
                        query2.addBindValue(parent);
                        query2.exec();
                        query2.next();
                        if(parent &&!query2.isValid())
                        {
                            query2.prepare("update Power set Del = ? where Mark = ?");
                            query2.addBindValue(del);
                            query2.addBindValue(parent);
                            query2.exec();
                            stop = 0;
                        }
                    }
                    query.prepare("delete from Power where Del = ?");
                    query.addBindValue(del);
                    query.exec();
                    if(stop){
                        break;
                    }
                }

            }
        }
    }
    else{ //非拥有者
        if(ui->checkBoxr->isChecked()){
            query.prepare("select * from Power where UserID= ? and ObjID= ? and Ability= ? and GiverID= ?");
            query.addBindValue(ui->UserName->text());
            query.addBindValue(ui->ObjName->text());
            query.addBindValue("r");
            query.addBindValue(globalname);
            query.exec();
            query.next();
            if(!query.isValid()){
                QMessageBox::warning(this,tr("Warning"),tr("r:此授权不存在!"),QMessageBox::Yes);
            }
            else{
                query.prepare("delete from Power where UserID= ? and ObjID= ? and Ability= ? and GiverID= ?");
                query.addBindValue(ui->UserName->text());
                query.addBindValue(ui->ObjName->text());
                query.addBindValue("r");
                query.addBindValue(globalname);
                query.exec();
            }

        }
        if(ui->checkBoxw->isChecked()){
            query.prepare("select * from Power where UserID= ? and ObjID= ? and Ability= ? and GiverID= ?");
            query.addBindValue(ui->UserName->text());
            query.addBindValue(ui->ObjName->text());
            query.addBindValue("w");
            query.addBindValue(globalname);
            query.exec();
            query.next();
            if(!query.isValid()){
                QMessageBox::warning(this,tr("Warning"),tr("w:此授权不存在!"),QMessageBox::Yes);
            }
            else{
                query.prepare("delete from Power where UserID= ? and ObjID= ? and Ability= ? and GiverID= ?");
                query.addBindValue(ui->UserName->text());
                query.addBindValue(ui->ObjName->text());
                query.addBindValue("w");
                query.addBindValue(globalname);
                query.exec();
            }
        }
        if(ui->checkBoxc->isChecked()){
            query.prepare("select * from Power where UserID= ? and ObjID= ? and Ability= ? and GiverID= ?");
            query.addBindValue(ui->UserName->text());
            query.addBindValue(ui->ObjName->text());
            query.addBindValue("c");
            query.addBindValue(globalname);
            query.exec();
            query.next();
            if(!query.isValid()){
                QMessageBox::warning(this,tr("Warning"),tr("c:此授权不存在!"),QMessageBox::Yes);
            }
            else{
                query.prepare("delete from Power where UserID= ? and ObjID= ? and Ability= ? and GiverID= ?");
                query.addBindValue(ui->UserName->text());
                query.addBindValue(ui->ObjName->text());
                query.addBindValue("c");
                query.addBindValue(globalname);
                query.exec();
                while(1){
                    del = 1;
                    stop = 1;
                    query.exec("select * from Power");
                    while(query.next()){
                        parent = query.value(5).toInt();
                        query2.prepare("select * from Power where No=?");
                        query2.addBindValue(parent);
                        query2.exec();
                        query2.next();
                        if(parent &&!query2.isValid())
                        {
                            query2.prepare("update Power set Del = ? where Mark = ?");
                            query2.addBindValue(del);
                            query2.addBindValue(parent);
                            query2.exec();
                            stop = 0;
                        } 
                    }
                    query.prepare("delete from Power where Del = ?");
                    query.addBindValue(del);
                    query.exec();
                    if(stop){
                        break;
                    }
                }
            }
        }
    }
    this->close();
}

void Withdraw::on_closeButton_clicked()
{
    this->close();
}

void Withdraw::on_checkBoxr_clicked(bool checked)
{
    //复选框设置
    //若选择撤销读权，且已经获得了控制权，则应同时撤销控制权
    QSqlQuery query;
    if(ui->ObjName->text() == ""){
        QMessageBox::warning(this,tr("Warning"),tr("请输入客体名称!"),QMessageBox::Yes);
        ui->ObjName->clear();
        ui->checkBoxr->setChecked(false);
        ui->checkBoxw->setChecked(false);
        ui->checkBoxc->setChecked(false);
        ui->ObjName->setFocus();
        return;
    }
    if(ui->UserName->text() == ""){
        QMessageBox::warning(this,tr("Warning"),tr("请输入主体名称!"),QMessageBox::Yes);
        ui->UserName->clear();
        ui->checkBoxr->setChecked(false);
        ui->checkBoxw->setChecked(false);
        ui->checkBoxc->setChecked(false);
        ui->ObjName->setFocus();
        return;
    }
    if(checked){
        isConnection();

        query.prepare("select * from Power where UserID= ? and ObjID= ? and Ability= ? and GiverID= ? ");
        query.addBindValue(ui->UserName->text());
        query.addBindValue(ui->ObjName->text());
        query.addBindValue("c");
        query.addBindValue(globalname);
        query.exec();
        query.next();
        if(query.isValid() && !ui->checkBoxc->isChecked())
        {
            ui->checkBoxc->setChecked(true);
        }
    }
    else{
        if(!ui->checkBoxw->isChecked())
            ui->checkBoxc->setChecked(false);
    }

}

void Withdraw::on_checkBoxw_clicked(bool checked)
{
    //复选框设置
    //若选择撤销写权，且已经获得了控制权，则应同时撤销控制权
    if(ui->ObjName->text() == ""){
        QMessageBox::warning(this,tr("Warning"),tr("请输入客体名称!"),QMessageBox::Yes);
        ui->ObjName->clear();
        ui->checkBoxr->setChecked(false);
        ui->checkBoxw->setChecked(false);
        ui->checkBoxc->setChecked(false);
        ui->ObjName->setFocus();
        return;
    }
    if(ui->UserName->text() == ""){
        QMessageBox::warning(this,tr("Warning"),tr("请输入主体名称!"),QMessageBox::Yes);
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
        query.addBindValue("c");
        query.addBindValue(globalname);
        query.exec();
        query.next();
        if(query.isValid() && !ui->checkBoxc->isChecked())
        {
            ui->checkBoxc->setChecked(true);
        }
    }
    else{
        if(!ui->checkBoxr->isChecked())
            ui->checkBoxc->setChecked(false);
    }

}
