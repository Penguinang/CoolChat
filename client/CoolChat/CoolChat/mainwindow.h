#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QtGUi>
#include <QLabel>
#include <QListWidget>
#include <QString>
#include <QStackedWidget>
#include <QPainter>
#include <QString>
#include <QCloseEvent>
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
    void get_text_callback(string username,string time,string content);
    ~MainWindow();
    void ShowChatWindow(string string = "Anon",int index = 0);
    void callback(vector<struct userinfo> &friends_list);
    void deleteFriend(string);
    void addFriend(string);
    QListWidget *list;
    QStackedWidget *m_cStackedWidget;
    Server* m_server;

private:  
    void paintEvent(QPaintEvent*);
    QPainter *paint;

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void AnotherWindow();
    void singleclicked(QListWidgetItem *item);

};

#endif // MAINWINDOW_H
