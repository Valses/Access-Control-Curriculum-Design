#include "powercreate.h"
#include "ui_powercreate.h"
#include "database.h"
PowerCreate::PowerCreate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PowerCreate)
{
    ui->setupUi(this);
    this->setWindowTitle("创建权限");
}

PowerCreate::~PowerCreate()
{
    delete ui;
}

void PowerCreate::on_yesButton_clicked()
{
    if(ui->lineEdit->text() == ""){
        QMessageBox::warning(this,"Warning","请输入权限名称!",QMessageBox::Yes);
        ui->lineEdit->setFocus();
        return;
    }
    if(!isConnection()){
        QMessageBox::warning(this,"Warning","无法连接到数据库!",QMessageBox::Yes);
        return;
    }
    QSqlQuery query;
    query.prepare("select * from Power where Power= ? ");
    query.addBindValue(ui->lineEdit->text());
    query.exec();
    query.next();
    if(query.isValid()){
        QMessageBox::warning(this,"Warning","权限已存在!",QMessageBox::Yes);
        ui->lineEdit->clear();
        ui->lineEdit->setFocus();
        return;
    }
    query.prepare("insert into Power (Power) values(?)");
    query.addBindValue(ui->lineEdit->text());
    query.exec();
    QMessageBox::warning(this,"Congratulations","权限已添加!",QMessageBox::Yes);
    accept();
}

void PowerCreate::on_closeButton_clicked()
{
    this->close();
}
