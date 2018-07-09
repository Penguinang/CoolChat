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
//#include "Server.h"

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
    QPixmap pix;
    void paintEvent(QPaintEvent *);
    //Server *m_server;
    void callback(std::vector<struct userinfo> &user_list);

signals:
public slots:
private slots:
    void SearchFriend();
    void windowclosed();
    void windowmin();
    void BtnListOnClicked();

};

#endif // ADDFRIEND_H
