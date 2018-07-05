#ifndef SINGALPERSON_H
#define SINGALPERSON_H
#include <QWidget>
#include <QLabel>
#include <QEvent>

class singalPerson:public QWidget
{
    Q_OBJECT
public:
    explicit singalPerson(QWidget *parent=0);
    void initUi();
    QLabel *name;// 用户名
    QLabel *sign;//个签
};

#endif // SINGALPERSON_H
