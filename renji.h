#ifndef RENJI_H
#define RENJI_H

#include <QWidget>
#include<QTimer>

#define GRID_NUMBER 8
#define WHITE_FLAG() (role == White) ? (whiteFlag = false) : true
#define BLACK_FLAG() (role == Black) ? (blackFlag = false) : true


namespace Ui {
class Renji;
}

class Renji : public QWidget
{
    Q_OBJECT

public:
    explicit Renji(QWidget *parent = 0);
    ~Renji();

    //用枚举标记黑白棋状态
    enum ChessFlag{Empty,Black,White};

    QPoint p;
    //起点坐标、终点坐标
    QPoint startPoint;
    QPoint endPoint;
    //每一格的高度与宽度
    int gridHigh;
    int gridWidth;

    bool whiteFlag; //白棋是否落子的标志位，落子则置为true，没落子直接替换角色则置为false
    bool blackFlag; //黑棋是否落子的标志位

    int bNumber;    //最终的黑棋统计
    int wNumber;    //最终的白棋统计

    bool overFlag;  //结束的QMessageBox::about()是否调用过的标志
                    //因为QMessageBox::about()如果不检测调用次数，会影响交互性

    //定义一个二维数组保存黑白棋的状态
    int chessStatus[8][8];

    //切换状态
    ChessFlag role; //有White和Black两种状态
    //切换角色
    void changeRole();
    //统计个数
    void countScore();

    QTimer timer;       //定时器，为了保证体验感，不至于机器下子太快

    //吃子规则的算法函数：棋盘坐标(x,y)、棋子当前角色
    //eatChess默认为true即吃子，fasle为检测了否吃子
    //N*N的每一列（行）格数默认为8
    int judgeRole(int x, int y, ChessFlag currentRole, bool eatChess = true);

    //机器下子
    void machinePlay();
    //游戏结束
    void gameOver();




    //棋盘初始化
    void initChess();
    //
    void paintEvent(QPaintEvent *parent);  //绘图事件：画棋盘，画棋子
    void mousePressEvent(QMouseEvent *ev);    //鼠标按下事件：获取当前点击的坐标、下子坐标
    void mouseMoveEvent(QMouseEvent *ev); //鼠标移动事件，用于移动窗口


signals:
    void back_lab();
    void back_fanhui();
    void back_over();


private slots:
    void on_toolButtonQuit_clicked();
    void on_toolButtonstart_clicked();

private:
    Ui::Renji *ui;
};

#endif // RENJI_H
