#ifndef QIPAN_H
#define QIPAN_H

#include <QWidget>

namespace Ui {
class Qipan;
}

class Qipan : public QWidget
{
    Q_OBJECT

public:
    explicit Qipan(QWidget *parent = 0);
    ~Qipan();
private:
    Ui::Qipan *ui;
};

#endif // QIPAN_H
