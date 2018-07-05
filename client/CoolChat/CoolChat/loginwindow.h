#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QMouseEvent>
#include <QPoint>
#include <QString>
#include "registerwindow.h"
#include <string>
//#include "server.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent=0);
    ~LoginWindow();

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:

    void paintEvent(QPaintEvent *);
    void getUserName();
    void getPassWord();
    void callback(bool,std::string);

    QLabel *userNameLabel;
    QLabel *passWordLabel;

    QPushButton *registerBtn;

    QLineEdit *userNameLineEdit;
    QLineEdit *passWordLineEdit;

    QPushButton *login;
    QPushButton *exit;
    QPushButton *min;

    bool mbKeepPressed;
    QPoint mPntStart;

    RegisterWindow *registerWindow;
    //Server *m_server;

    QString g_username;
    QString g_password;


private slots:
    void windowclosed();
    void windowmin();
    void slotLogin();
    void slotRegister();

};

#endif // LOGINWINDOW_H
