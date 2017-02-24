#include "login.h"
#include "ui_login.h"

bool isAdmin;
QString globalname;

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    isConnection();
    ui->pwdEdit -> setEchoMode(QLineEdit::Password);
    this->setWindowTitle("登录");
    QSqlQuery q;
    q.exec("select UserID from User");
    while(q.next()){
        this->ui->comboBox->addItem(q.value(0).toString());
    }
    ui->uaButton->setText("管理员");
    this->show();
}

Login::~Login()
{
    delete ui;
}


void Login::on_signInButton_clicked()
{
    if(ui->pwdEdit->text()==tr("")){
        QMessageBox::warning(this,"Warning","请输入密码!",QMessageBox::Yes);
        ui->pwdEdit->clear();
        ui->pwdEdit->setFocus();
        return;
    }
    if(ui->uaButton->text()==tr("用户"))
    {
        QString password =this->ui->pwdEdit->text();
        if(password == "123456"){
            //globalname = name;
            isAdmin = true;
            win1 = new MainWindow;
            win1->show();
            this->close();
            return;
        }
        else{
            QMessageBox::critical(this, "wrong", "密码错误!", 0, 0);
            return;
        }

    }
    else
    {
        QString name =this->ui->comboBox->currentText();
        QString password =this->ui->pwdEdit->text();
        QSqlQuery q;
        q.exec("select * from User where UserID = ?");
        q.addBindValue(name);
        q.exec();
        q.next();
        if(q.value(1).toString() == password){
            globalname = name;
            isAdmin = false;
            this->win1 = new MainWindow;
            this->win1->show();
            this->close();
            return;
        }
        else{
            QMessageBox::critical(this, "wrong", "密码错误!", 0, 0);
            return;
        }
    }
}

void Login::on_signUpButton_clicked()
{
    this->win2 = new SignUp;
    connect(win2,
            SIGNAL(on_loginWindowFinishedSignal()),
            this,
            SLOT(on_loginWindowFinished()));
    win2->show();
}

void Login::on_loginWindowFinished()
{
    qDebug() << "login";
    if(ui->uaButton->text()==tr("用户")){
        ui->comboBox->clear();
        ui->comboBox->addItem("Admin");
    }
    else{
        this->ui->comboBox->clear();
        QSqlQuery q;
        q.exec("select UserID from User");
        while(q.next()){
            this->ui->comboBox->addItem(q.value(0).toString());
        }
        qDebug() << "tianjia";
    }
}

void Login::on_uaButton_clicked()
{
    if(ui->uaButton->text()==tr("管理员"))
    {
        ui->comboBox->clear();
        ui->comboBox->addItem("Admin");
        ui->signUpButton->setEnabled(false);
        ui->uaButton->setText("用户");
        ui->pwdEdit->clear();
        ui->pwdEdit->setFocus();
    }
    else
    {
        ui->comboBox->clear();
        QSqlQuery q;
        q.exec("select UserID from User");
        while(q.next()){
            this->ui->comboBox->addItem(q.value(0).toString());
        }
        ui->uaButton->setText("管理员");
        ui->signUpButton->setEnabled(true);
        ui->pwdEdit->clear();
        ui->pwdEdit->setFocus();
    }
}
