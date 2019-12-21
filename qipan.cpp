#include "qipan.h"
#include "ui_qipan.h"

Qipan::Qipan(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Qipan)
{
    ui->setupUi(this);

}

Qipan::~Qipan()
{
    delete ui;
}


