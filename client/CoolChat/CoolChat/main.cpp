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
    Server* m_server=new Server (string ip = "localhost", int port，void(*get_text_callback)(string username, string time, string content));
    LoginWindow w(0,m_server);
    w.show();
    return a.exec();
}
