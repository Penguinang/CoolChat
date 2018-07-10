#ifndef ADDFRIEND_H
#define ADDFRIEND_H

#include <QWidget>
#include <QtGUi>
#include <QLineEdit>
#include <QString>
#include <QPaintEvent>
#include <QPushButton>
#include <QGridLayout>
#include <QPixmap>
#include <QLabel>
#include "string.h"
#include "string"
#include <string>
#include <server.h>
#include <mainwindow.h>

using namespace std ;

class AddFriend:public QWidget
{
    Q_OBJECT
public:
    Server *m_server;
    QGridLayout *pLayout;
    QWidget* pWidget;
    QLineEdit *input;
    QPushButton* min;//最小化按钮
    QPushButton* exit;//退出按钮
    string str[5];
    MainWindow *mainwin;

    explicit AddFriend(QWidget *parent=0,Server *server=NULL,MainWindow *mainwin);
    ~AddFriend();
    void callback();

private:
    void paintEvent(QPaintEvent *);


signals:
public slots:
    void SearchFriend();
    void windowclosed();
    void windowmin();
    void BtnListOnClicked();
private slots:


};

#endif // ADDFRIEND_H
