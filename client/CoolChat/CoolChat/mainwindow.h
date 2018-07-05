#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <addfriend.h>
#include <chatwindow.h>
#include <QWidget>
#include <QtGUi>
#include <QLabel>
#include <QListWidget>
#include <QString>
#include <QStackedWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    void chat();
    AddFriend *addWindow;
    QStackedWidget *m_cStackedWidget;

private slots:
    void AnotherWindow();
    void ShowChatWindow(QString string = "Anon",int index = 0);

};

#endif // MAINWINDOW_H
