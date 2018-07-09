#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <addfriend.h>
#include <chatwindow.h>
#include <chatwindow.h>
#include <QWidget>
#include <QtGUi>
#include <QLabel>
#include <QListWidget>
#include <QString>
#include <QStackedWidget>
#include <QPainter>
#include <QString>
#include <server.h>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0,Server *server);
    ~MainWindow();

private:
    void chat();
    AddFriend *addWindow;
    ChatWindow *chatWindow;
    QStackedWidget *m_cStackedWidget;
    //好友列表框
    void paintEvent(QPaintEvent*);
    QPainter *paint;
    //好友列表
    QPushButton *button[];
    Server *m_server;

protected:
    void callback();
    void ShowChatWindow(string string = "Anon",int index = 0);
private slots:
    void AnotherWindow();
    void buttonOnClicked();
};

#endif // MAINWINDOW_H
