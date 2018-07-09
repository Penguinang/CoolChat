#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>
#include <QLineEdit>
#include <QLabel>
//#include <server.h>

class RegisterWindow : public QWidget
{
    Q_OBJECT
public:
    explicit RegisterWindow(QWidget *parent = 0,Server *server);
    ~RegisterWindow();

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool getUsername();
    bool getPassword();
    bool getConfirmpw();
    bool getEmail();

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
    Server m_server;
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
    void paintEvent(QPaintEvent *);
    void showTips(QString);

};

#endif // REGISTERWINDOW_H
