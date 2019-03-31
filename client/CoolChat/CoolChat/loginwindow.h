#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "Server.h"
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QMouseEvent>
#include <QPoint>
#include <QString>
#include "registerwindow.h"
#include "mainwindow.h"
#include <string>

class RegisterWindow;

const string ip = "10.14.222.28";
const int port = 9123;

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent=0);
    ~LoginWindow();

    Server *m_server;

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

    QString g_username;
    QString g_password;

    QLabel* tips;//提示消息
    bool m_tips;//提示消息是否出现

    MainWindow* mainwin;

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool getUserName();
    bool getPassWord();
    void callback(bool,std::string);
    bool checkUserName(QString);
    void showTips(QString);

private:
    void paintEvent(QPaintEvent *);

private slots:
    void windowclosed();
    void windowmin();
    void slotLogin();
    void slotRegister();
    void hideTips();
    void hideTips_1();
    void hideTips_2();
    void hideTips_3();

};

#endif // LOGINWINDOW_H
