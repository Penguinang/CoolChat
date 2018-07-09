#include "mainwindow.h"
#include "loginwindow.h"
#include "chatwindow.h"
#include "registerwindow.h"
#include "applicationwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ApplicationWindow w;
    w.show();
    return a.exec();
}
