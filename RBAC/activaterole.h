#ifndef ACTIVATEROLE_H
#define ACTIVATEROLE_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class ActivateRole;
}

class ActivateRole : public QDialog
{
    Q_OBJECT

public:
    explicit ActivateRole(QWidget *parent = 0);
    ~ActivateRole();
    bool isMutex( QString role);
    void activateChildRole(QString role);

private slots:
    void on_yesButton_clicked();

    void on_closeButton_clicked();

private:
    Ui::ActivateRole *ui;
};

#endif // ACTIVATEROLE_H
