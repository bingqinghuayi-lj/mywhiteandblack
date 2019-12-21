#include "register.h"
#include "ui_register.h"
#include <QPushButton>
#include <QString>
#include <stdio.h>
#include <QDebug>
#include <QMessageBox>
#include "QTextEdit"
#include <QPixmap>
#include <stdio.h>
#include <QSize>
Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    //设置大小
    this->setFixedSize(800,600);
    //背景图片
    QPalette pal = this->palette();
    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/image_qi/yun1.jpg.png")));
    setPalette(pal);

    //返回主页
    connect(ui->buttonback,&QPushButton::clicked,[=]
    {
        emit this->mysigner();
    });
    //重新输入
    connect(ui->buttonclear,&QPushButton::clicked,[=]{
        ui->lineedituser->clear();
        ui->lineeditpasswd->clear();
        ui->lineeditagein->clear();
    });

    //判断注册
    connect(ui->buttontrue,&QPushButton::clicked,[=]
    {
        if(ui->lineedituser->text() == NULL && ui->lineeditpasswd->text() == NULL)
        {
            QMessageBox::critical(this,"错误","用户名或密码不能为空");
        }
        else if(ui->lineeditpasswd->text() != ui->lineeditagein->text())
        {
            QMessageBox::critical(this,"错误","两次输入的密码不同，重新输入");
            ui->lineeditpasswd->text().clear();
            ui->lineeditagein->text().clear();
        }

        else
        {
            FILE *fp = fopen("C:/Users/28903/Desktop/chess.txt","a+");
            if(fp == NULL)
            {
                perror("fopen");
                return;
            }

            QString str=ui->lineedituser->text();
            char* str1;
            QByteArray ba=str.toLatin1();
            str1=ba.data();
            fputs(str1,fp);
            fprintf(fp,":");
            QString mima=ui->lineeditpasswd->text();
            char* str2;
            QByteArray ba1=mima.toLatin1();
            str2=ba1.data();
            fputs(str2,fp);
            fprintf(fp,"\n");
            QMessageBox::information(this, "正确", "注册成功");
            fclose(fp);
        }


    });
}

Register::~Register()
{
    delete ui;
}
