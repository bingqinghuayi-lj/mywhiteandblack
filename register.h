#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>

namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = 0);
    ~Register();
signals:
    void mysigner(void);

private:
    Ui::Register *ui;
};

#endif // REGISTER_H
