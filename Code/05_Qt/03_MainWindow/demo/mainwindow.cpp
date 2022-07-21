#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPushButton *btA = new QPushButton(this);
    btA->move(10,10);
    btA->setFixedSize(200,200);

    QPushButton *btB = new QPushButton(btA);
    btB->move(10,10);
    btB->setFixedSize(150,150);

    QPushButton *btC = new QPushButton(btB);
    btC->move(10,10);
    btC->setFixedSize(100,100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

