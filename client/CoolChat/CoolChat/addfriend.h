#ifndef ADDFRIEND_H
#define ADDFRIEND_H

#include <QWidget>
#include <QtGUi>
#include <QLineEdit>
#include <QString>

class AddFriend:public QWidget
{
    Q_OBJECT
public:
    explicit AddFriend(QWidget *parent=0);
    ~AddFriend();
private:
    QLineEdit *input;

signals:
public slots:
private slots:
    void SearchFriend();

};

#endif // ADDFRIEND_H
