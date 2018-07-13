#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include "Server.h"
#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>
#include <QLineEdit>
#include <QLabel>

class RegisterWindow : public QWidget
{
    Q_OBJECT
public:
    explicit RegisterWindow(QWidget *parent,Server *server);
    ~RegisterWindow();

    Server* m_server;
    QPushButton *registerBtn;
    QPushButton *exit;
    QPushButton *min;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QLineEdit *confirmEdit;
    QLineEdit *emailEdit;
    bool mbKeepPressed;
    QPoint mPntStart;
    QString r_username;
    QString r_password;
    QString r_confirmpw;
    QString r_email;
    QLabel* tips;//提示消息
    bool m_tips;//提示消息是否出现

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool getUsername();
    bool getPassword();
    bool getConfirmpw();
    bool getEmail();
    void showTips(QString);

signals:

public slots:

private slots:
    void windowclosed();
    void windowmin();
    void slotRegister();
    void hideTips();
    void hideTips_1();
    void hideTips_2();
    void hideTips_3();

private:

    void paintEvent(QPaintEvent *);


};

#endif // REGISTERWINDOW_H
