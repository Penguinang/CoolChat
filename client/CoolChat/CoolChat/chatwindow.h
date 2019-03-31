#ifndef CHATWINDOW_H
#define CHATWINDOW_H

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

using Netmodule::Server;

namespace Ui {
class ChatWindow;
}

class ChatWindow : public QWidget
{
    Q_OBJECT

public:
    ChatWindow(Server *server,QWidget *parent = 0,QString chatID = "Anon",int chatHeight=800,int chatWidth=800,MainWindow* mainwin=NULL);
    ~ChatWindow();
    void callback(bool);
    void showFailureTips(QString);
    void sendMsgShow(QString,QString);
    void recvMsgShow(QString,QString);

    QLabel* friendName;//好友名称
private:
    Ui::ChatWindow *ui;
    QString chatID;
    QPushButton* min;//最小化按钮
    QPushButton* exit;//退出按钮
    QPushButton* sentBtn;//发送按钮
    QPushButton* deleteBtn;
    QWebEngineView* msgShowWindow;//消息显示框
    QTextEdit* msgEditWindow;//消息编辑框
    QString msgInEdit;//输入框中的文字信息
    QLabel* tips;//提示消息
    bool m_tips;//提示消息是否出现
    QString m_head;
    QString f_head;
    QString m_html;
    Server *m_server;
    MainWindow* mainwin;

    void paintEvent(QPaintEvent *);


protected:
    bool eventFilter(QObject *,QEvent *);

private slots:
    void windowclosed();
    void windowmin();
    void sentBtnOnClicked();
    void deleteBtnOnClicked();
    void hideFailureTips();
    void hideFailureTips_1();
    void hideFailureTips_2();
    void hideFailureTips_3();//实现渐变效果
};

#endif // CHATWINDOW_H
