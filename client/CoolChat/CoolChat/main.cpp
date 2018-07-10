#include "mainwindow.h"
#include "loginwindow.h"
#include "chatwindow.h"
#include "registerwindow.h"
#include "applicationwindow.h"
#include "addfriend.h"
#include "Server.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow w(0);
    w.show();
    return a.exec();
}
