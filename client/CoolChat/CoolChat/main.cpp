#include "loginwindow.h"

#include <QApplication>
#include <iostream>
using namespace std;

//#define null nullptr
int main(int argc, char *argv[])
{
    int c = 0;
    c+=1;
    int b = 0;
    b+=0;
    QApplication a(argc, argv);
    LoginWindow w(0);
    w.show();
    return a.exec();
}
