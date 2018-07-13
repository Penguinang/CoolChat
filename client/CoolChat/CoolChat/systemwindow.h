#ifndef SystemWindow_H
#define SystemWindow_H
#include "Server.h"
#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QString>
#include <QPushButton>
#include <QPaintEvent>
#include <QPoint>
#include <QWebEngineView>
#include <mainwindow.h>


namespace Ui {
class SystemWindow;
}

class SystemWindow : public QWidget
{
    Q_OBJECT

public:
    SystemWindow(Server *server,QWidget *parent=0,QString chatID = "Anon",int chatHeight=800,int chatWidth=800,MainWindow* mainwin=NULL);
    ~SystemWindow();
    void recvMsgShow(QString,QString);
    void showTips(QString);
    QLabel* tips;//提示消息
    bool m_tips;//提示消息是否出现
    bool newmsg;
    QString chatID;
    QPushButton* min;//最小化按钮
    QPushButton* exit;//退出按钮
    QPushButton* agreeBtn;//同意按钮
    QPushButton* refuseBtn;//拒绝按钮
    QLabel* friendName;//好友名称
    QWebEngineView* msgShowWindow;//消息显示框
    QTextEdit* msgEditWindow;//消息编辑框
    QString msgInEdit;//输入框中的文字信息
    QString m_head;
    QString f_head;
    QString m_html;
    Server *m_server;
    string username;
    MainWindow* mainwin;

private:
    Ui::SystemWindow *ui;




    void paintEvent(QPaintEvent *);


protected:

private slots:
    void windowclosed();
    void windowmin();
    void agreeBtnOnClicked();
    void refuseBtnOnClicked();
    void hideTips();
    void hideTips_1();
    void hideTips_2();
    void hideTips_3();
};

#endif // SystemWindow_H
