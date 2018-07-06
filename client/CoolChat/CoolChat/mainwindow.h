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

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    void chat();
    AddFriend *addWindow;
    ChatWindow *chatWindow;
    QStackedWidget *m_cStackedWidget;
    //好友列表框
    void paintEvent(QPaintEvent*);
    QPainter *paint;

private slots:
    void AnotherWindow();
    void ShowChatWindow_1();
    void ShowChatWindow_2();

};

#endif // MAINWINDOW_H
