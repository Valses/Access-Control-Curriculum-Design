#include "objdelete.h"
#include "ui_objdelete.h"
#include "database.h"

extern QString globalname;

ObjDelete::ObjDelete(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ObjDelete)
{
    ui->setupUi(this);
    this->setWindowTitle("删除客体");
}

ObjDelete::~ObjDelete()
{
    delete ui;
}


void ObjDelete::on_deleteButton_clicked()
{
    if(ui->ObjName->text() == ""){
        QMessageBox::warning(this,"Warning","请输入客体名称!",QMessageBox::Yes);
        ui->ObjName->setFocus();
        return;
    }
    else{
        if(!isConnection()){
            QMessageBox::warning(this,"Warning","无法连接到数据库!",QMessageBox::Yes);
            return;
        }
        QSqlQuery query;
        query.prepare("select * from Object where ObjID= ? ");
        query.addBindValue(ui->ObjName->text());
        query.exec();
        query.next();
        if(!query.isValid()){ //客体不存在于列表
            QMessageBox::warning(this,tr("Warning"),tr("客体不存在!"),QMessageBox::Yes);
            ui->ObjName->clear();
            ui->ObjName->setFocus();
            return;
        }
        query.prepare("select * from Object where ObjID= ? and UserID= ? ");
        query.addBindValue(ui->ObjName->text());
        query.addBindValue(globalname);
        query.exec();
        query.next();

        if(!query.isValid()){ //客体不属于该主体
            QMessageBox::warning(this,tr("Warning"),tr("没有权限删除此客体!"),QMessageBox::Yes);
            ui->ObjName->clear();
            ui->ObjName->setFocus();
            return;
        }
        else{
            query.prepare("delete from Object where OBJID= ? ");
            query.addBindValue(ui->ObjName->text());
            query.exec();
            query.prepare("delete from Power where ObjID= ? ");
            query.addBindValue(ui->ObjName->text());
            query.exec();
            query.prepare("delete from BlackList where ObjID= ? ");
            query.addBindValue(ui->ObjName->text());
            query.exec();
            QMessageBox::warning(this,"Congratulations","删除成功!",QMessageBox::Yes);
            accept();
        }
    }
}

void ObjDelete::on_closeButton_clicked()
{
    this->close();
}

