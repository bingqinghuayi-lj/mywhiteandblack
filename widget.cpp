#include "widget.h"
#include "ui_widget.h"
#include "register.h"
#include "maindow.h"
#include <QBrush>
#include <QPixmap>
#include <QPalette>
#include <QMessageBox>
#include <QPainter>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //设置窗口大小
    this->setFixedSize(1200,600);
    //背景图片
    QPalette pal = this->palette();
    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/image_qi/lig1.jpg")));
    setPalette(pal);

    //新建注册窗口
    Register *registers = new Register;
    connect(ui->buttonregister,&QPushButton::clicked,[=]
    {
        this->hide();
        registers->show();
    });
    //创建游戏窗口
    Maindow *maindow = new Maindow;

    //返回登录
    connect(registers,&Register::mysigner,[=]
    {
        registers->hide();
        this->show();
    });
    //清空
    connect(ui->buttonclear,&QPushButton::clicked,[=]
    {
        ui->lineuser->clear();
        ui->linepasswd->clear();
    });
    //退出
    connect(ui->buttonquit,&QPushButton::clicked,this,&Widget::close);
    //登录
    connect(ui->buttonlig,&QPushButton::clicked,[=]
    {
        FILE *fp;
        if ((fp = fopen("C:/Users/28903/Desktop/chess.txt","r+")) == NULL)
        {
            perror("fail to fopen");
            return;
        }
        fseek(fp, 0, SEEK_END);
        long int len = ftell(fp);
        char *lrc = (char *)malloc(len + 1);
        fseek(fp, 0, SEEK_SET);
        fread(lrc, len, 1, fp);
        char *str[256] = {NULL};
        int i = 0;
        str[i] = strtok(lrc, "\n");
        while (str[i] != NULL)
        {
            i++;
            str[i] = strtok(NULL, "\n");
        }
        fclose(fp);

        QString s1=ui->lineuser->text();
        char* sss;
        QByteArray ba1=s1.toLatin1();
        sss=ba1.data();

        QString s2=ui->linepasswd->text();
        char* sss_1;
        QByteArray ba2=s2.toLatin1();
        sss_1=ba2.data();

        char *p=NULL;
        char *pp=NULL;
        char *p1=NULL;
        for(int j=0;j<i;j++)
        {
            pp=NULL;
            p1=new char[strlen(str[j])+1];
            p=p1;
            strcpy(p1,str[j]);
            while(*p!=':')
            {
                p++;
            }p++;
            pp=strtok(str[j],":");
            //delete p1;

            if(qstrcmp(sss,pp)==0)
            {
                if(qstrcmp(sss_1,p)==0)
                {
                    QMessageBox::information(this, "正确", "登录成功");
                    maindow->show();
                    this->hide();
                    delete p1;
                    return ;
                }

            }


        }


        QMessageBox::critical(this, "错误", "您输入有误，请重新输入");

        delete p1;
    });
}

Widget::~Widget()
{
    delete ui;
}
