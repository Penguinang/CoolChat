#include "singalperson.h"
#include <QPainter>

singalPerson::singalPerson(QWidget *parent):
    QWidget(parent)
{
    //初始化
    name = new QLabel(this);
    sign = new QLabel(this);
    //设置个性签名字体为灰色
    QPalette color;
    color.setColor(QPalette::Text,Qt::gray);
    sign->setPalette(color);
    //布局
    name->move(54,10);
    sign->move(54,27);
}
