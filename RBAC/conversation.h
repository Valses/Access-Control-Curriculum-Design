#ifndef CONVERSATION_H
#define CONVERSATION_H

#include <QDialog>
#include <QMessageBox>
#include <QDebug>
namespace Ui {
class Conversation;
}

class Conversation : public QDialog
{
    Q_OBJECT

public:
    explicit Conversation(QWidget *parent = 0);
    ~Conversation();
    bool isMutex(QString role);
    void addInPower(QString role);


private:
    Ui::Conversation *ui;
    QStringList powerlist1, powerlist2;
};

#endif // CONVERSATION_H
