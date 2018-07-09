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
//#include "Server.h"

using namespace std ;

class AddFriend:public QWidget
{
    Q_OBJECT
public:
    explicit AddFriend(QWidget *parent=0);
    ~AddFriend();
private:
    QGridLayout *pLayout;
    QWidget* pWidget;
    QLineEdit *input;
    QPushButton* min;//最小化按钮
    QPushButton* exit;//退出按钮
    string str[5];
    void paintEvent(QPaintEvent *);
    //Server *m_server;
    void callback();

signals:
public slots:
private slots:
    void SearchFriend();
    void windowclosed();
    void windowmin();
    void BtnListOnClicked();

};

#endif // ADDFRIEND_H
