#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "testbtn.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    testBtn *bt = new testBtn(this);
    bt->show();
    bt->setFixedSize(100,100);
}

MainWindow::~MainWindow()
{
    delete ui;
}

