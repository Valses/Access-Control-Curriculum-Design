#include "objcreate.h"
#include "ui_objcreate.h"

#include "database.h"

extern QString globalname;

ObjCreate::ObjCreate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ObjCreate)
{
    ui->setupUi(this);
    this->setWindowTitle("创建客体");
}

ObjCreate::~ObjCreate()
{
    delete ui;
}

void ObjCreate::on_createButton_clicked()
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

        if(query.isValid()){
            QMessageBox::warning(this,"Warning","客体已存在!",QMessageBox::Yes);
            ui->ObjName->clear();
            ui->ObjName->setFocus();
            return;
        }
        else{
            int mark = 0, del = 0;
            int num = 1;
            query.exec("select * from Power");
            if(query.last()){
                num=query.value(0).toInt();
                num++;
            }
            query.prepare("insert into Object (ObjID, UserID) values (?, ?)");
            query.addBindValue(ui->ObjName->text());
            query.addBindValue(globalname);
            query.exec();
            query.prepare("insert into Power (No, UserID, ObjID, Ability, GiverID, Mark, Del) values (?, ?, ?, ?, ?, ?, ?)");
            query.addBindValue(num);
            query.addBindValue(globalname);
            query.addBindValue(ui->ObjName->text());
            query.addBindValue("o");
            query.addBindValue("-");
            query.addBindValue(mark);
            query.addBindValue(del);
            query.exec();
            QMessageBox::warning(this, "Congratulations", "客体创建成功!",QMessageBox::Yes);
            accept();
        }
    }
}

void ObjCreate::on_closeButton_clicked()
{
    this->close();
}
