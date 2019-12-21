#include "peopleqipan.h"
#include "ui_peopleqipan.h"
#include<QPixmap>
#include<QPainter>
#include<QTimer>
#include<QMessageBox>
#include<QPushButton>
#include<QString>
#include <vector>
QVector<int> v1;
bool result = true;
int time_num = 0;
Peopleqipan::Peopleqipan(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Peopleqipan)
{
    ui->setupUi(this);
    init_arr();//初始化

    connect(ui->pushButton_new, &QPushButton::clicked,[=](){
        this->hide();
        this->show();
        init_arr();
        countScore();
        time_jishi->stop();
    });


    connect(ui->pushButton_2,&QPushButton::clicked,[=](){
        nandu = true;
    });
    connect(ui->pushButton_3,&QPushButton::clicked,[=](){
        nandu = false;
    });


    connect(ui->pushButton_back,&QPushButton::clicked,[=](){
        emit this->back();
    });
    //创建一个定时器
    time_jishi = new QTimer(this);
    time_delayed = new QTimer(this);
    //让定时器动起来
    connect(time_jishi,&QTimer::timeout,[=](){
        //static int num = 0;
        //ui->lcdNumber_3->setText(QString::number(num++));
        int iftime = 10-time_num++;
        ui->lcdNumber_3->display(iftime);
        if(iftime == 0)
        {
            if(flag == true)
            {
                QMessageBox::about(this,"超时","白棋获得胜利");
            }
            else
            {
                QMessageBox::about(this,"超时","黑棋获得胜利");
            }

        }
    });
}

Peopleqipan::~Peopleqipan()
{
    delete ui;
}

void Peopleqipan::paintEvent(QPaintEvent *parent)
{
    QPixmap pix;
    pix.load(":/image_qi/yun3.jpg.png");
    //修改图片大小
    pix = pix.scaled(624,580);
    //定义一个画家
    QPainter *paint = new QPainter(this);
    paint->drawPixmap(this->rect(),QPixmap(":image_qi/yun2.jpg.png"));
    for(int i = 0;i<9;i++)
    {
        paint->drawLine(143,99+60*i,626,99+60*i);
    }
    for(int i = 0;i<9;i++)
    {
        paint->drawLine(143+60*i,99,143+60*i,580);
    }

    //初始化棋盘
    QPixmap pix1;
    pix1.load(":/image_qi/white.png");
    pix1 = pix1.scaled(50,50);
    QPixmap pix2;
    pix2.load(":/image_qi/black.png");
    pix2 = pix2.scaled(50,50);
    QPixmap pix4;
    pix4.load(":/image_qi/yun2.jpg.png");
    pix4 = pix4.scaled(60,60);
    for(int i = 0;i<8;i++)
    {
        for(int j = 0;j<8;j++)
        {
            if( arr[i][j] == 2)
            {
                paint->drawPixmap(146+60*i,101+60*j,pix2.width(),pix2.height(),pix2);
            }
            else if(arr[i][j] == 1)
            {
                paint->drawPixmap(146+60*i,101+60*j,pix1.width(),pix1.height(),pix1);
            }
        }
    }

    //落子位置提示
    QPixmap pix3;
    pix3.load(":/image_qi/victory.jpg");
    pix3 = pix3.scaled(50,50);
    myarr2();//初始化提示位置
    eatnum();
    while (arr2[a1][0] != 10)
    {
        paint->drawPixmap(146+60*arr2[a1][0],101+60*arr2[a1][1],pix3.width(),pix3.height(),pix3);
        a1++;
    }
    a1 = 0;
    //显示当前落子方
    if(flag == true)
    {
        ui->label_2->setPixmap(pix2);
    }
    else
    {
        ui->label_2->setPixmap(pix1);
    }
}

void Peopleqipan::mousePressEvent(QMouseEvent *event)
{

    if(event->button() == Qt::LeftButton)
    {
        //获取鼠标单击点坐标
        x1 = event->x() - 144;
        y2 = event->y() - 100;
        //qDebug()<<x1<<" "<<y2;
        // myarr2();//初始化提示位置
        // eatnum();//获取提示位置
        if(x1>0 && y2>0)
        {
            x1 = x1/60;
            y2 = y2/60;
            //更改数组信息
            if((eatchess(x1,y2)) && ((x1<8) && (y2<8) && (x1>=0) && (y2>=0)))
            {
                time_jishi->stop();//----------------停止计时----------
                time_num = 0;
                if(flag == true)
                {
                    flag = false;//更改落子方标志
                    arr[x1][y2] = 2;
                    time_jishi->start(1000);//-----------------启动计时
                    //muisc_b->play();
                }
                else
                {
                    flag =true;
                    arr[x1][y2] = 1;
                    time_jishi->start(1000);//-----------------启动计时
                    //muisc_w->play();
                }
                this->repaint();
                this->update();
                countScore();
                myarr2();//初始化提示位置
                eatnum();

                while(patern == false && flag == false && nandu == true)
                {
                    //muisc_w->play();
                    myarr2();//初始化提示位置
                    eatnum();
                    eatchess(arr2[0][0],arr2[0][1]);
                    arr[arr2[0][0]][arr2[0][1]] = 1;
                    flag = true;
                    //time_delayed->start(1500);
                    for(int n =0 ; n < 1000 ; n++)
                    {
                        for(int m = 0 ; m < 1000 ; m++)
                        {
                            for(int t = 0 ; t < 500 ; t++)
                            {

                            }
                        }
                    }
                    this->update();
                    countScore();
                }

                while(patern == false && flag == false && nandu == false)
                {
                    //muisc_w->play();
                    myarr2();//初始化提示位置
                    eatnum();
                    int i = suiji();
                    eatchess(arr2[i][0],arr2[i][1]);
                    arr[arr2[i][0]][arr2[i][1]] = 1;
                    flag = true;
                    //time_delayed->start(1500);
                    for(int n =0 ; n < 1000 ; n++)
                    {
                        for(int m = 0 ; m < 1000 ; m++)
                        {
                            for(int t = 0 ; t < 100 ; t++)
                            {

                            }
                        }
                    }
                    this->update();
                    countScore();
                }
            }
        }
    }
}

void Peopleqipan::timerEvent(QTimerEvent *event)
{

}

void Peopleqipan::countScore()
{
    bNumber = 0;    //最终的黑棋统计
    wNumber = 0;    //最终的白棋统计
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++)
        {
            (!(arr[i][j] - 1))? bNumber++ : ((!(arr[i][j] - 2)) ? wNumber++ : true);
        }
    }
    ui->lcdNumber->display(bNumber);
    ui->lcdNumber_2->display(wNumber);
    result = flag_Result();
    if(!result)
    {
        gameOver();
        //init_arr();
    }
}

bool Peopleqipan::flag_Result()
{
    if((bNumber+wNumber)<64 && bNumber!=0 && wNumber!=0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Peopleqipan::gameOver()
{
    if(wNumber < bNumber)
    {
        QMessageBox::about(this,"白棋嬴","白棋获得胜利");
    }
    else if(wNumber > bNumber)
    {
        QMessageBox::about(this,"黑棋嬴","黑棋获得胜利");
    }
    else if(wNumber == bNumber)
    {
        QMessageBox::about(this,"平局","平分秋色");
    }
}

void Peopleqipan::eatnum()
{
    int tmpX=0,tmpY=0,current,s=0,num=0,u1=0,u2=0,u3 = 0;
    int dir[8][2] = {{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1}};
    if(flag == true)
    {
        current = 2;
    }
    else if(flag == false)
    {
        current = 1;
    }
    for(int i = 0;i<8;i++)
    {
        for(int j = 0;j<8;j++)
        {
            if(arr[i][j] == 0)
            {
                tmpX = i;
                tmpY = j;
                for(int r = 0;r<8;r++)
                {
                    tmpX += dir[r][0];
                    tmpY += dir[r][1];
                    if((tmpX<8 && tmpY<8 && tmpX>=0 && tmpY>=0) && (arr[tmpX][tmpY] != current)&& (arr[tmpX][tmpY] != 0))
                    {
                        s++;//记录吃子个数
                        tmpX += dir[r][0];
                        tmpY += dir[r][1];//在当前方向 向前走一步
                        while (tmpX<8 && tmpY<8 && tmpX>=0 && tmpY>=0)
                        {
                            if(arr[tmpX][tmpY] == 0){
                                break;//遇到空的位置 跳出循环
                            }
                            if(arr[tmpX][tmpY] == current)//找到自己的棋子 可以吃子了
                            {
                                arr2[u1++][0] = i;
                                arr2[u2++][1] = j;
                                num++;
                            }
                            s++;
                            tmpX += dir[r][0];
                            tmpY += dir[r][1];
                        }
                    }
                    tmpX = i,tmpY = j;
                }
                s = 0;
            }
        }
    }
    if(num == 0)
    {
        flag = !flag;
    }
}

int Peopleqipan::eatchess(int a_x, int b_y)
{
    int t = 0;
    //八个落子方向
    int dir[8][2] = {{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1}};
    int tmpX = a_x,tmpY = b_y;//保存棋盘坐标位置
    int current;
    //如果方格中已有棋子 直接返回
    if(arr[tmpX][tmpY] != 0)
    {
        return 0;
    }
    else if(flag == true)
    {
        current = 2;
    }
    else if(flag == false)
    {
        current = 1;
    }
    for(int i = 0;i<8;i++)
    {
        //确定一个方向
        tmpX += dir[i][0];
        tmpY += dir[i][1];
        //棋子没有出界 而且是对方棋子才有可能吃
        if((tmpX<8 && tmpY<8 && tmpX>=0 && tmpY>=0) && (arr[tmpX][tmpY] != current)&& (arr[tmpX][tmpY] != 0))
        {
            tmpX += dir[i][0];
            tmpY += dir[i][1];//在当前方向 向前走一步
            while (tmpX<8 && tmpY<8 && tmpX>=0 && tmpY>=0)
            {
                if(arr[tmpX][tmpY] == 0){
                    break;//遇到空的位置 跳出循环
                }
                if(arr[tmpX][tmpY] == current)//找到自己的棋子 可以吃子了
                {
                    tmpX -= dir[i][0];
                    tmpY -= dir[i][1];
                    while (tmpX != a_x || tmpY != b_y)
                    {
                        arr[tmpX][tmpY] = current;
                        tmpX -= dir[i][0];
                        tmpY -= dir[i][1];
                        t++;
                        //qDebug()<<t;
                    }
                    break;
                }
                tmpX += dir[i][0];
                tmpY += dir[i][1];
            }
        }
        tmpX = a_x,tmpY = b_y;
    }
    this->update();
    countScore();
    return t;
}

int Peopleqipan::vtr()
{
    v1.clear();
    srand(time(NULL));
    int i =0;
    while(arr2[i][0] != 10)
    {
        v1.push_back(i);
    }
    //random_shuffle(v1.begin(),v1.end());
    return v1[0];
}

int Peopleqipan::suiji()
{
    srand(time(NULL));
    int i = 0,j = 0;
    while (arr2[i][0] != 10)
    {
        i++;
        j++;
    }
    int k = (int)rand%(j+1);
    return k;
}

void Peopleqipan::on_pushButton_clicked()
{
    init_arr();
    this->update();
}
bool patern;
bool nandu = true;
bool flag = true;
int x1 = 0;
int y2 = 0;
int arr[8][8] = {0};
void init_arr()
{
    for(int i=0;i<8;i++)
    {
        for(int j = 0;j<8;j++)
        {
            arr[i][j] = 0;
        }
    }
    arr[3][3] = 1;
    arr[3][4] = 2;
    arr[4][3] = 2;
    arr[4][4] = 1;
    flag = true;//黑子先下
}

int a1=0;
int arr3[64] = {0};
void paixu()
{
    int i = 0,max,j;
    for(;i<63;i++)
    {
        for(j = 1+i,max = i;j<64;j++)
        {
            if (arr3[max]<arr3[j])
            {
                max = j;
            }

        }
        if(max != i)
        {
            int tmp = arr3[i];
            arr3[i] = arr3[max];
            arr3[max] = tmp;
        }
    }
}

int arr2[64][2] = {0};
void myarr2()
{
    for(int i=0;i<64;i++)
    {
        arr2[i][0] = 10;
        arr2[i][1] = 10;
    }
}
