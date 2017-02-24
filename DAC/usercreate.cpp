#include "usercreate.h"
#include "ui_usercreate.h"

#include "database.h"

UserCreate::UserCreate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserCreate)
{
    ui->setupUi(this);
    ui-> pwd1 -> setEchoMode(QLineEdit::Password);
    ui-> pwd2 -> setEchoMode(QLineEdit::Password);
    this->setWindowTitle("注册");
}

UserCreate::~UserCreate()
{
    delete ui;
}

void UserCreate::on_pushButton_clicked()
{
    QString name = this->ui->userName->text();
    QString password1 = this->ui->pwd1->text();
    QString password2 = this->ui->pwd2->text();
    if(name == "" || password1 == "" || password2 == ""){
        QMessageBox::warning(this,"Warning","请重新输入!",QMessageBox::Yes);
        ui->userName->setFocus();
        return;
    }
    if(operator !=(password2, password1)){
        QMessageBox::warning(this,"Warning","密码不一致，请重新输入!",QMessageBox::Yes);
        ui->pwd1->clear();
        ui->pwd2->clear();
        ui->pwd1->setFocus();
        return;
    }

    QString info = 0;
    if(!isConnection()){
        QMessageBox::warning(this,"Warning","无法连接到数据库!",QMessageBox::Yes);
        return;
    }
    QSqlQuery q;
    q.prepare("select * from User where UserID = ?");
    q.addBindValue(name);
    q.exec();
    q.next();
    if(q.isValid()){//用户名已存在
        QMessageBox::warning(this,"Warning","用户名已存在!",QMessageBox::Yes);
        ui->userName->clear();
        ui->pwd1->clear();
        ui->pwd2->clear();
        ui->userName->setFocus();
        return;
    }
    q.prepare("insert into User (UserID, passwd, info) values(:name,:password1,:info)");
    q.bindValue(0, name);
    q.bindValue(1, password1);
    q.bindValue(2, info);
    q.exec();

    QMessageBox::information(this, "Information", "成功注册");

    emit on_loginWindowFinishedSignal();
    this->close();
}
