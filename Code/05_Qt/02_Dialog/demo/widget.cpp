#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    testDialog *dl = new testDialog(this);
    dl->show();     //非模态对话框
//    dl->exec();   //模态对话框
}

Widget::~Widget()
{
    delete ui;
}

