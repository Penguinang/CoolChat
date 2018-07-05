#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>

class RegisterWindow : public QWidget
{
    Q_OBJECT
public:
    explicit RegisterWindow(QWidget *parent = 0);
    ~RegisterWindow();

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);


signals:

public slots:

private slots:
    void windowclosed();
    void windowmin();

private:

    QPushButton *registerBtn;
    QPushButton *exit;
    QPushButton *min;
    bool mbKeepPressed;
    QPoint mPntStart;

    void paintEvent(QPaintEvent *);
    void slotRegister();
};

#endif // REGISTERWINDOW_H
