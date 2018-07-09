#ifndef APPLICATIONWINDOW_H
#define APPLICATIONWINDOW_H
#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QString>
#include <server.h>

class ApplicationWindow: public QWidget
{
    Q_OBJECT
public:
    ApplicationWindow(QWidget *parent=0,QString string = NULL,Server *server);

private:
    Server m_server;
    QTextEdit *application;
    QPushButton* min;//最小化按钮
    QPushButton* exit;//退出按钮
    QString userId;
    void paintEvent(QPaintEvent *);

private slots:
    void sendBtnOnClicked();
    void windowclosed();
    void windowmin();
};

#endif // APPLICATIONWINDOW_H
