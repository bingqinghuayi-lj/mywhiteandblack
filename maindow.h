#ifndef MAINDOW_H
#define MAINDOW_H

#include <QWidget>
#include <vector>
namespace Ui {
class Maindow;
}

class Maindow : public QWidget
{
    Q_OBJECT

public:
    explicit Maindow(QWidget *parent = 0);
    ~Maindow();

    void switchPage();//棋盘切换

private:
    Ui::Maindow *ui;
};

#endif // MAINDOW_H

