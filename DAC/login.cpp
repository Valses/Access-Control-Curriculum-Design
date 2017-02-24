#include "login.h"
#include "ui_login.h"
#include "database.h"

QString globalname;

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->pwdBox -> setEchoMode(QLineEdit::Password);
    this->setWindowTitle("登录");
    if(!isConnection()){
        QMessageBox::warning(this,"Warning","Unable to connect to database!",QMessageBox::Yes);
        return;
    }
    QSqlQuery q;
    q.exec("select UserID from User");
    while(q.next()){
        this->ui->comboBox->addItem(q.value(0).toString());
    }
    this->show();
}

Login::~Login()
{
    delete ui;
}


void Login::on_sign_in_clicked()
{
    if(ui->pwdBox->text()==tr("")){
        QMessageBox::warning(this,"Warning","请输入密码!",QMessageBox::Yes);
        ui->pwdBox->clear();
        ui->pwdBox->setFocus();
        return;
    }
    else{
        QString name =this->ui->comboBox->currentText();
        QString password =this->ui->pwdBox->text();
        QSqlQuery q;
        q.exec("select * from User where UserID = ?");
        q.addBindValue(name);
        q.exec();
        q.next();
        if(q.value(1).toString() == password){
            globalname = name;
            this->win1 = new MainWindow;

            this->win1->show();
            this->close();
            return;
        }
        else{
            QMessageBox::critical(this, "wrong", "密码错误!", 0, 0);
            return;
        }
        QMessageBox::warning(this,"Warning","没有这个用户!",0,0);
    }
}

void Login::on_sign_up_clicked()
{
    this->win2 = new UserCreate;
    connect(this->win2,
            SIGNAL(on_loginWindowFinishedSignal()),
            this,
            SLOT(on_loginWindowFinished()));
    this->win2->show();
}

void Login::on_loginWindowFinished()
{
    this->ui->comboBox->clear();
    QSqlQuery q;
    q.exec("select UserID from User");
    while(q.next()){
        this->ui->comboBox->addItem(q.value(0).toString());
    }
}

