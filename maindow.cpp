#include "maindow.h"
#include "ui_maindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QMouseEvent>
#include<QPixmap>
#include<QPainter>
#include<QTimer>
#include<QPushButton>
#include<QString>
#include <QWidget>
#include <QPaintEvent>
#include<vector>
#include<stdlib.h>
#include <numeric>
#include <time.h>
#include "renji.h"
Maindow::Maindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Maindow)
{
    ui->setupUi(this);
    //设置窗口信息
    this->setWindowTitle("黑白棋");
    this->setFixedSize(1195,1000);

    //对战提示信息
    int ret;
    connect(ui->buttonpeople,&QPushButton::clicked,[&](int ret)
    {
        ret = QMessageBox::question(this,"提示信息","你确定要进行人人对战吗？");
        if(ret == QMessageBox::Yes)
        {
            QMessageBox::information(this,"玩家名","已为你分配好name");
            ui->lineedituser1->setText("黎明使者");
            ui->lineedituser2->setText("黑夜使者");
        }
        else
        {
            QMessageBox::information(this,"取消","你取消了人人对战");
        }
    });
    connect(ui->buttonal,&QPushButton::clicked,[=]
    {
        QMessageBox::information(this,"AI","你即将对战高级AI！");
    });
    connect(ui->buttonstart,&QPushButton::clicked,[=]
    {
        QMessageBox::information(this,"提示","游戏已开始");
    });
    //将人人对战，人机对战，开始游戏建立联系
    connect(ui->buttonpeople,&QPushButton::clicked,this,&Maindow::switchPage);
    connect(ui->buttonal,&QPushButton::clicked,this,&Maindow::switchPage);

    //进入黑白棋
    Renji *renji = new Renji;
    connect(ui->buttonal,&QPushButton::clicked,[=]
    {
        //this->hide();
        renji->show();
    });
    //返回主页
    connect(renji,&Renji::back_lab,[=]()
    {
        renji->hide();
        this->show();
    });
}

Maindow::~Maindow()
{
    delete ui;
}
//人人对战人机对战按钮联系
void Maindow::switchPage()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if(button==ui->buttonpeople)
        ui->stackedWidget->setCurrentIndex(0);
    if(button==ui->buttonal)
        ui->stackedWidget->setCurrentIndex(1);
}
