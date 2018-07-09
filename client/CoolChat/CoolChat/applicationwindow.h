#ifndef APPLICATIONWINDOW_H
#define APPLICATIONWINDOW_H
#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QString>

class ApplicationWindow: public QWidget
{
    Q_OBJECT
public:
    ApplicationWindow(QWidget *parent=0,QString string);

private:
    QTextEdit *application;
    QPushButton* min;//最小化按钮
    QPushButton* exit;//退出按钮
    QString userId;
    void paintEvent(QPaintEvent *);
    //Server *m_server;

private slots:
    void sendBtnOnClicked();
    void windowclosed();
    void windowmin();
};

#endif // APPLICATIONWINDOW_H
