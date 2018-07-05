#include "chatwindow.h"


#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QString>
#include <QPushButton>
#include <QFont>
#include <QPaintEvent>
#include <QPainter>
#include <QRect>
#include <QPalette>
#include <QPen>
#include <QPixmap>
#include <QTimer>
#include <QGraphicsOpacityEffect>
#include <QSplitter>
#include <QWebEngineView>

//#include "Server.h"

/*
 * 聊天窗口Constructor
 * @param parent 窗口父类
 * @param chatID 当前聊天对象
 * @param chatHeight 窗口高度
 * @param chatWidth 窗口宽度
 */
ChatWindow::ChatWindow(QWidget *parent,QString chatID,int chatHeight,int chatWidth)
    :QWidget(parent)
{
    this->chatID = chatID;
    this->setWindowFlags(Qt::FramelessWindowHint| Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setMaximumSize(chatWidth,chatHeight);
    this->setMinimumSize(chatWidth,chatHeight);

    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);

    exit = new QPushButton(this);
    exit->setStyleSheet("QPushButton{border-image:url(:/new/img/img/exit.png);}"
                        "QPushButton:hover{border-image:url(:/new/img/img/exit1.png);}"
                        "QPushButton:pressed{border-image:url(:/new/img/img/exit.png);}");
    exit->setMinimumHeight(40);
    exit->setMinimumWidth(50);
    exit->move(chatWidth-50,0);
    min = new QPushButton(this);
    min->setStyleSheet("QPushButton{border-image:url(:/new/img/img/min.png);}"
                       "QPushButton:hover{border-image:url(:/new/img/img/min2.png);}"
                       "QPushButton:pressed{border-image:url(:/new/img/img/min.png);}");
    min->setMinimumHeight(40);
    min->setMinimumWidth(50);
    min->move(chatWidth-100,0);

    connect(exit,SIGNAL(clicked()),this,SLOT(windowclosed()));
    connect(min,SIGNAL(clicked()),this,SLOT(windowmin()));

    friendName = new QLabel(chatID,this);
    friendName -> setFont(QFont("Microsoft YaHei", chatHeight/30, 0));
    friendName -> adjustSize();
    friendName -> move(0,10);

    QWidget* w_splitter = new QWidget(this);
    w_splitter->setMaximumHeight(chatHeight-friendName->height()-100);
    w_splitter->setMaximumWidth(chatWidth);
    w_splitter->setMinimumHeight(chatHeight-friendName->height()-100);
    w_splitter->setMinimumWidth(chatWidth);
    w_splitter->move(5,friendName->height()+20);

    QSplitter* chatSplitter = new QSplitter(Qt::Vertical,w_splitter);
    chatSplitter->setMinimumWidth(w_splitter->width()-10);
    chatSplitter->setMaximumWidth(w_splitter->width()-10);
    chatSplitter->setMinimumHeight(w_splitter->height()-10);
    chatSplitter->setMaximumHeight(w_splitter->height()-10);
    msgShowWindow = new QWebEngineView;
    msgEditWindow = new QTextEdit;
    chatSplitter->addWidget(msgShowWindow);
    chatSplitter->addWidget(msgEditWindow);
    chatSplitter->adjustSize();
    //msgShowWindow->setStyleSheet("QWebEngineView{background-color:rgb(250,250,250);border:none;}");
    msgEditWindow->setStyleSheet("QTextEdit{border:rgb(100,100,100)}");
    chatSplitter->setStretchFactor(0,7);
    chatSplitter->setStretchFactor(1,3);

    QFont *font=new QFont("Microsoft YaHei",12,0);
    font->setLetterSpacing(QFont::AbsoluteSpacing,0.5);
    sentBtn = new QPushButton(tr("SEND"),this);
    sentBtn->setFont(*font);
    sentBtn->setPalette(pa);
    sentBtn->setStyleSheet("QPushButton{background-color:rgb(0,162,232);border:2px groove white;border-radius:10px;padding:2px 4px;color:white;}"
                           "QPushButton:pressed{background-color:rgb(153,217,234);}");
    sentBtn->setMinimumHeight(40);
    sentBtn->setMinimumWidth(100);
    sentBtn->move(chatWidth-120,chatHeight-60);

    connect(sentBtn,SIGNAL(clicked()),this,SLOT(sentBtnOnClicked()));

}
ChatWindow::~ChatWindow()
{

}

void ChatWindow::windowclosed()
{
    this->close();
}

void ChatWindow::windowmin()
{
    this->showMinimized();
}

void ChatWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(255,255,255));
    QRect rect = this->rect();
    rect.setWidth(rect.width()-1);
    rect.setHeight(rect.height()-1);
    p.drawRect(rect);
    p.setPen(QPen(QColor(200,200,200),1));
    p.drawRect(0,0,this->width(),this->height());
}

void ChatWindow::sentBtnOnClicked()
{
    //msgInEdit = msgEditWindow->toPlainText();
    //std::string s_msgInEdit = msgInEdit.toStdString();
    //std::string s_chatId = this->chatID.toStdString();
    //调用服务器功能，向好友发送文字信息
    //void (ChatWindow::*pCallback)(bool,std::string)= &ChatWindow::callback;
    //m_server->SendText(s_chatId,s_msgInEdit,pCallback);

    //假设失败，显示消息发送失败提醒框
    callback(false);
}

void ChatWindow::callback(bool success)
{
    //若消息发送失败，显示消息框提醒
    if(success == false)
    {
        this->showFailureTips();
        QTimer::singleShot(3000,this,SLOT(hideFailureTips()));
        QTimer::singleShot(2700,this,SLOT(hideFailureTips_1()));
        QTimer::singleShot(2800,this,SLOT(hideFailureTips_2()));
        QTimer::singleShot(2900,this,SLOT(hideFailureTips_3()));
    }
    //若消息发送成功，在消息显示框中显示消息
    else
    {

    }
}

//提示：消息发送失败
void ChatWindow::showFailureTips()
{
    tips = new QLabel(this);
    tips->setMaximumHeight(50);
    tips->setMinimumHeight(50);
    QFont *font=new QFont("Microsoft YaHei",12,0);
    tips->setFont(*font);
    tips->setText("Message Send failed!");
    tips->setStyleSheet("QLabel{background-color:rgb(107,107,107);color:white;border-radius:10px;padding:2px 4px;}");
    tips->adjustSize();
    tips->move((this->width()-tips->width())/2,(this->height()-tips->height())/2);
    tips->show();
}

//提示消息框渐变隐藏消失
void ChatWindow::hideFailureTips()
{
    tips->hide();
}

void ChatWindow::hideFailureTips_1()
{
    QGraphicsOpacityEffect *opacityEffect=new QGraphicsOpacityEffect;
    tips->setGraphicsEffect(opacityEffect);
    opacityEffect->setOpacity(0.8);
}

void ChatWindow::hideFailureTips_2()
{
    QGraphicsOpacityEffect *opacityEffect=new QGraphicsOpacityEffect;
    tips->setGraphicsEffect(opacityEffect);
    opacityEffect->setOpacity(0.5);
}

void ChatWindow::hideFailureTips_3()
{
    QGraphicsOpacityEffect *opacityEffect=new QGraphicsOpacityEffect;
    tips->setGraphicsEffect(opacityEffect);
    opacityEffect->setOpacity(0.2);
}

