#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"
#include "login.h"

extern bool isAdmin;
extern QString globalname;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("RBAC");

    QString s1 = tr("Welcome "),s2,s3 = ("!");
    qDebug() << isAdmin;
    if(isAdmin){
        s2 = "Admin";
        ui->welcomeLabel->setText(s1+s2+s3);
        ui->clearButton->setEnabled(false);
        ui->label1->setText("全部用户情况");
        ui->label2->setText("用户当前激活情况");
        //ui->tableView2->setHidden(true);
        ui->activateButton->setEnabled(false);
        ui->sButton->setEnabled(false);
        ui->inactiveButton->setEnabled(false);
        //qDebug() << isAdmin;
        ui->tabWidget->setCurrentIndex(0);

        table1 = new QSqlTableModel(this);
        table1->setTable("User");
        table1->setEditStrategy(QSqlTableModel::OnManualSubmit);
        table1->select();
        table1->removeColumn(1);
        ui->tableView1->setModel(table1);
        ui->tableView1->setEditTriggers(QAbstractItemView::NoEditTriggers);

        table2 = new QSqlTableModel(this);
        table2->setTable("ActiveU");
        table2->setEditStrategy(QSqlTableModel::OnManualSubmit);
        table2->select();
        table2->removeColumn(0);
        ui->tableView2->setModel(table2);
        ui->tableView2->setEditTriggers(QAbstractItemView::NoEditTriggers);

        table3 = new QSqlTableModel(this);
        table3->setTable("Role");
        table3->setEditStrategy(QSqlTableModel::OnManualSubmit);
        table3->select();
        ui->tableView3->setModel(table3);
        ui->tableView3->setEditTriggers(QAbstractItemView::NoEditTriggers);

        table4 = new QSqlTableModel(this);
        table4->setTable("Power");
        table4->setEditStrategy(QSqlTableModel::OnManualSubmit);
        table4->select();
        ui->tableView4->setModel(table4);
        ui->tableView4->setEditTriggers(QAbstractItemView::NoEditTriggers);

        table5 = new QSqlTableModel(this);
        table5->setTable("UR");
        table5->setEditStrategy(QSqlTableModel::OnManualSubmit);
        table5->select();
        table5->removeColumn(0);
        ui->tableView5->setModel(table5);
        ui->tableView5->setEditTriggers(QAbstractItemView::NoEditTriggers);

        table6 = new QSqlTableModel(this);
        table6->setTable("PR");
        table6->setEditStrategy(QSqlTableModel::OnManualSubmit);
        table6->select();
        table6->removeColumn(0);
        ui->tableView6->setModel(table6);
        ui->tableView6->setEditTriggers(QAbstractItemView::NoEditTriggers);

        table7 = new QSqlTableModel(this);
        table7->setTable("RH");
        table7->setEditStrategy(QSqlTableModel::OnManualSubmit);
        table7->select();
        table7->removeColumn(0);
        ui->tableView7->setModel(table7);
        ui->tableView7->setEditTriggers(QAbstractItemView::NoEditTriggers);

        table8 = new QSqlTableModel(this);
        table8->setTable("Mutex");
        table8->setEditStrategy(QSqlTableModel::OnManualSubmit);
        table8->select();
        table8->removeColumn(0);
        ui->tableView8->setModel(table8);
        ui->tableView8->setEditTriggers(QAbstractItemView::NoEditTriggers);

        MainWindow::drawTree();

    }
    else{
        s2 = globalname;
        ui->label1->setText("拥有角色情况");
        ui->welcomeLabel->setText(s1+s2+s3);

        /*
         * 设置按钮不可点击
        ui->crePowButton->setEnabled(false);
        ui->creRolButton->setEnabled(false);
        ui->delPowButton->setEnabled(false);
        ui->delRolButton->setEnabled(false);
        ui->urButton->setEnabled(false);
        ui->durButton->setEnabled(false);
        ui->rpButton->setEnabled(false);
        ui->drpButton->setEnabled(false);
        ui->rhButton->setEnabled(false);
        ui->drhButton->setEnabled(false);
        ui->rrButton->setEnabled(false);
        ui->drrButton->setEnabled(false);
        */
        //设置tab隐藏
        ui->tabWidget->removeTab(1);
        ui->tabWidget->removeTab(1);
        ui->tabWidget->setCurrentIndex(0);
        //qDebug() << isAdmin;
        //hide()，close()，setHidden(true)，setVisible(false)

        table1 = new QSqlTableModel(this);
        table1->setTable("UR");
        table1->setFilter(QObject::tr("User = '%1'").arg(globalname));
        table1->setEditStrategy(QSqlTableModel::OnManualSubmit);
        table1->select();
        table1->removeColumn(0);
        ui->tableView1->setModel(table1);
        ui->tableView1->setEditTriggers(QAbstractItemView::NoEditTriggers);


        table2 = new QSqlTableModel(this);
        table2->setTable("ActiveU");
        table2->setFilter(QObject::tr("User = '%1'").arg(globalname));
        table2->setEditStrategy(QSqlTableModel::OnManualSubmit);
        table2->select();
        table2->removeColumn(0);
        ui->tableView2->setModel(table2);
        ui->tableView2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_creRolButton_clicked()
{
    RoleCreate win;
    win.exec();
    if(!isConnection()){
        return;
    }
    table3 = new QSqlTableModel(this);
    table3->setTable("Role");
    table3->setEditStrategy(QSqlTableModel::OnManualSubmit);
    table3->select();
    ui->tableView3->setModel(table3);
    ui->tableView3->setEditTriggers(QAbstractItemView::NoEditTriggers);



}

void MainWindow::on_delRolButton_clicked()
{
    RoleDelete win;
    win.exec();
    if(!isConnection()){
        return;
    }

    drawTree();

    table2 = new QSqlTableModel(this);
    table2->setTable("ActiveU");
    table2->setEditStrategy(QSqlTableModel::OnManualSubmit);
    table2->select();
    table2->removeColumn(0);
    ui->tableView2->setModel(table2);
    ui->tableView2->setEditTriggers(QAbstractItemView::NoEditTriggers);

    table3 = new QSqlTableModel(this);
    table3->setTable("Role");
    table3->setEditStrategy(QSqlTableModel::OnManualSubmit);
    table3->select();
    ui->tableView3->setModel(table3);
    ui->tableView3->setEditTriggers(QAbstractItemView::NoEditTriggers);

    table5 = new QSqlTableModel(this);
    table5->setTable("UR");
    table5->setEditStrategy(QSqlTableModel::OnManualSubmit);
    table5->select();
    table5->removeColumn(0);
    ui->tableView5->setModel(table5);
    ui->tableView5->setEditTriggers(QAbstractItemView::NoEditTriggers);

    table6 = new QSqlTableModel(this);
    table6->setTable("PR");
    table6->setEditStrategy(QSqlTableModel::OnManualSubmit);
    table6->select();
    table6->removeColumn(0);
    ui->tableView6->setModel(table6);
    ui->tableView6->setEditTriggers(QAbstractItemView::NoEditTriggers);

    table7 = new QSqlTableModel(this);
    table7->setTable("RH");
    table7->setEditStrategy(QSqlTableModel::OnManualSubmit);
    table7->select();
    table7->removeColumn(0);
    ui->tableView7->setModel(table7);
    ui->tableView7->setEditTriggers(QAbstractItemView::NoEditTriggers);

    table8 = new QSqlTableModel(this);
    table8->setTable("Mutex");
    table8->setEditStrategy(QSqlTableModel::OnManualSubmit);
    table8->select();
    table8->removeColumn(0);
    ui->tableView8->setModel(table8);
    ui->tableView8->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

void MainWindow::on_crePowButton_clicked()
{
    PowerCreate win;
    win.exec();
    if(!isConnection()){
        return;
    }
    table4 = new QSqlTableModel(this);
    table4->setTable("Power");
    table4->setEditStrategy(QSqlTableModel::OnManualSubmit);
    table4->select();
    ui->tableView4->setModel(table4);
    ui->tableView4->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::on_delPowButton_clicked()
{
    PowerDelete win;
    win.exec();
    qDebug() << "1";
    if(!isConnection()){
        return;
    }
    qDebug() << "2";
    table4 = new QSqlTableModel(this);
    table4->setTable("Power");
    table4->setEditStrategy(QSqlTableModel::OnManualSubmit);
    table4->select();
    ui->tableView4->setModel(table4);
    ui->tableView4->setEditTriggers(QAbstractItemView::NoEditTriggers);

    table5 = new QSqlTableModel(this);
    table5->setTable("UR");
    table5->setEditStrategy(QSqlTableModel::OnManualSubmit);
    table5->select();
    table5->removeColumn(0);
    ui->tableView5->setModel(table5);
    ui->tableView5->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

void MainWindow::on_uChangeButton_clicked()
{
    this->close();
    Login win;
    win.exec();
}

void MainWindow::on_clearButton_clicked()
{
    QMessageBox::StandardButton rep = QMessageBox::question(this, "warning", "确定注销用户？", QMessageBox::Yes|QMessageBox::No, QMessageBox::No);
    if(rep == QMessageBox::Yes) {
        if(!isConnection()){
            QMessageBox::warning(this,"Warning","无法连接到数据库!",QMessageBox::Yes);
            return;
        }
        QSqlQuery query;
        query.prepare("delete from User where UserID = ?");
        query.addBindValue(globalname);
        query.exec();
        query.prepare("delete from UR where User = ?");
        query.addBindValue(globalname);
        query.exec();
        this->close();
        Login win;
        win.exec();
    }
}

void MainWindow::on_exitButton_clicked()
{
    QApplication::exit(0);
}

void MainWindow::on_urButton_clicked()
{
    URACreate win;
    win.exec();
    if(!isConnection()){
        return;
    }
    table5 = new QSqlTableModel(this);
    table5->setTable("UR");
    table5->setEditStrategy(QSqlTableModel::OnManualSubmit);
    table5->select();
    table5->removeColumn(0);
    ui->tableView5->setModel(table5);
    ui->tableView5->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::on_durButton_clicked()
{
    URADelete win;
    win.exec();
    if(!isConnection()){
        return;
    }
    table5 = new QSqlTableModel(this);
    table5->setTable("UR");
    table5->setEditStrategy(QSqlTableModel::OnManualSubmit);
    table5->select();
    table5->removeColumn(0);
    ui->tableView5->setModel(table5);
    ui->tableView5->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::on_rpButton_clicked()
{
    PRACreate win;
    win.exec();
    if(!isConnection()){
        return;
    }
    table6 = new QSqlTableModel(this);
    table6->setTable("PR");
    table6->setEditStrategy(QSqlTableModel::OnManualSubmit);
    table6->select();
    table6->removeColumn(0);
    ui->tableView6->setModel(table6);
    ui->tableView6->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

void MainWindow::on_drpButton_clicked()
{
    PRADelete win;
    win.exec();
    if(!isConnection()){
        return;
    }
    table6 = new QSqlTableModel(this);
    table6->setTable("PR");
    table6->setEditStrategy(QSqlTableModel::OnManualSubmit);
    table6->select();
    table6->removeColumn(0);
    ui->tableView6->setModel(table6);
    ui->tableView6->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

void MainWindow::on_rrButton_clicked()
{
    MutexCreate win;
    win.exec();
    if(!isConnection()){
        return;
    }
    table8 = new QSqlTableModel(this);
    table8->setTable("Mutex");
    table8->setEditStrategy(QSqlTableModel::OnManualSubmit);
    table8->select();
    table8->removeColumn(0);
    ui->tableView8->setModel(table8);
    ui->tableView8->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::on_drrButton_clicked()
{
    MutexDelete win;
    win.exec();
    if(!isConnection()){
        return;
    }
    table8 = new QSqlTableModel(this);
    table8->setTable("Mutex");
    table8->setEditStrategy(QSqlTableModel::OnManualSubmit);
    table8->select();
    table8->removeColumn(0);
    ui->tableView8->setModel(table8);
    ui->tableView8->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::on_rhButton_clicked()
{
    RHCreate win;
    win.exec();
    if(!isConnection()){
        return;
    }
    drawTree();

    table7 = new QSqlTableModel(this);
    table7->setTable("RH");
    table7->setEditStrategy(QSqlTableModel::OnManualSubmit);
    table7->select();
    table7->removeColumn(0);
    ui->tableView7->setModel(table7);
    ui->tableView7->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::on_drhButton_clicked()
{
    RHDelete win;
    win.exec();
    if(!isConnection()){
        return;
    }
    drawTree();
    table7 = new QSqlTableModel(this);
    table7->setTable("RH");
    table7->setEditStrategy(QSqlTableModel::OnManualSubmit);
    table7->select();
    table7->removeColumn(0);
    ui->tableView7->setModel(table7);
    ui->tableView7->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::on_activateButton_clicked()
{
    ActivateRole win;
    win.exec();
    if(!isConnection()){
        return;
    }
    table2 = new QSqlTableModel(this);
    table2->setTable("ActiveU");
    table2->setFilter(QObject::tr("User = '%1'").arg(globalname));
    table2->setEditStrategy(QSqlTableModel::OnManualSubmit);
    table2->select();
    table2->removeColumn(0);
    //table2->removeColumn(1);
    ui->tableView2->setModel(table2);
    ui->tableView2->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::on_sButton_clicked()
{
    Conversation win;
    win.exec();
    if(!isConnection()){
        return;
    }

}

void MainWindow::on_inactiveButton_clicked()
{
    InanctiveRole win;
    win.exec();
    if(!isConnection()){
        return;
    }
    table2 = new QSqlTableModel(this);
    table2->setTable("ActiveU");
    table2->setFilter(QObject::tr("User = '%1'").arg(globalname));
    table2->setEditStrategy(QSqlTableModel::OnManualSubmit);
    table2->select();
    table2->removeColumn(0);
    ui->tableView2->setModel(table2);
    ui->tableView2->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::drawTree(){
    if(!isConnection()){
        return;
    }
    ui->treeWidget->clear();
    ui->treeWidget->setColumnCount(1);
    QSqlQuery query;
    QStringList list;
    QString nodef, nodec;
    int i, fi, ci;
    query.exec("select * from RH");
    while(query.next()){
        nodef = query.value(1).toString();
        nodec = query.value(2).toString();
        if(list.indexOf(nodef) == -1){
            list.append(nodef);
            i = list.length();
            item[i - 1] = new QTreeWidgetItem(ui->treeWidget,QStringList(nodef));
            //item[i - 1]->setIcon()
            fi = i-1;
            qDebug() << fi;
            qDebug() << nodef;
        }
        else{
            fi = list.indexOf(nodef);
        }
        if(list.indexOf(nodec) == -1){
            list.append(nodec);
            i = list.length();
            item[i - 1] = new QTreeWidgetItem(item[fi],QStringList(nodec));
            ci = i-1;
            qDebug() << ci;
            qDebug() << nodec;
        }
        else{
            ci = list.indexOf(nodec);
        }

        qDebug() << list;
        item[fi]->addChild(item[ci]);
        qDebug() << "add";
        //画树
    }
    ui->treeWidget->expandAll();
}

