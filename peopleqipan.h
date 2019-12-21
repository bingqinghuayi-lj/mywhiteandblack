#ifndef PEOPLEQIPAN_H
#define PEOPLEQIPAN_H

#include <QWidget>
#include <QPaintEvent>
#include <QVector>
#include <stdlib.h>
#include <numeric>
#include <time.h>


namespace Ui {
class Peopleqipan;
}

class Peopleqipan : public QWidget
{
    Q_OBJECT

public:
    explicit Peopleqipan(QWidget *parent = 0);
    ~Peopleqipan();
    //绘图
    void paintEvent(QPaintEvent *parent);
    //落子
    void mousePressEvent(QMouseEvent *event);
    //重写定时器
    void timerEvent(QTimerEvent *event);
    QTimer *time_jishi;
     QTimer *time_delayed;
    int time_num;

    int bNumber;    //最终的黑棋统计
    int wNumber;    //最终的白棋统计
    //统计成绩
    void countScore();
    //标记结束
    bool result;
    bool flag_Result();
    //游戏结束
    void gameOver();

    void eatnum();//落点吃子数
    int eatchess(int a_x,int b_y);//吃子
    int vtr();
    int suiji();
signals:
    void back();
    void start();
    void stop();
    void open_lab();
private slots:
    void on_pushButton_clicked();
private:
    Ui::Peopleqipan *ui;
    int x0;
    int y0;
};
extern bool patern;//游戏模式标志
extern bool nandu;//人机难度
extern bool flag;//落子方标志 true为黑子走
extern int arr[8][8];//二维数组存放棋子信息 0空 1白 2黑
extern void init_arr();//初始化棋盘
extern int arr2[64][2];//落子位置
extern int arr3[64];//吃子数目
extern void paixu();
extern void myarr2();
extern int a1;
//extern int arr3[64];//落子处 能够吃子的数目
extern int x1;//鼠标单击横坐标位置
extern int y2;//鼠标单击纵坐标位置
//extern int eatchess(int a_x,int b_y);//吃子
//extern void eatnum();//落点吃子数
#endif // PEOPLEQIPAN_H
