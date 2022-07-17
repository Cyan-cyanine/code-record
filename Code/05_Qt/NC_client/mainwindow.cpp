#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Client");
    ui->sendBuf->setDisabled(true);
    ui->disConnect->setDisabled(true);
    ui->port->setText("10086");
    ui->ip->setText("127.0.0.1");
    m_server = new QTcpServer(this);
    ui->statusbar->addWidget(new QLabel("连接状态:"));
    m_status = new QLabel();
    ui->statusbar->addWidget(m_status);
    m_status->setPixmap(QPixmap(":/disconnect.png"));
    m_tcp = new QTcpSocket(this);

    // 检测是否和服务器是否连接成功了
    connect(m_tcp, &QTcpSocket::connected, this, [=]()
    {
        connected=true;
        ui->histroy->append("连接服务器成功...");
        ui->disConnect->setEnabled(true);
        ui->sendBuf->setEnabled(true);
        m_status->setPixmap(QPixmap(":/connect.png"));
    });

    connect(m_tcp, &QTcpSocket::readyRead, this,[=]()
   {
       // 接收服务器发送的数据
       QByteArray recvMsg = m_tcp->readAll();
       ui->histroy->append("服务器:" + recvMsg);
   });


   // 检测服务器是否和客户端断开了连接
   connect(m_tcp, &QTcpSocket::disconnected, this, [=]()
   {
       connected=false;
       ui->histroy->append("已断开连接...");
       m_status->setPixmap(QPixmap(":/disconnect.png"));
       ui->connect->setEnabled(true);
       ui->disConnect->setEnabled(false);
   });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sndBtn_clicked()
{
    if(connected)
    {
        QString sndContent = ui->sendBuf->toPlainText();
        ui->histroy->append("客户端:"+sndContent);
        m_tcp->write(sndContent.toUtf8());
        ui->sendBuf->clear();
    }
}

void MainWindow::on_connect_clicked()
{
    qint16 port = ui->port->text().toUShort();
    QString ip = ui->ip->text();
    m_tcp->connectToHost(QHostAddress(ip), port);
    ui->connect->setDisabled(true);
}

void MainWindow::on_disConnect_clicked()
{
    m_tcp->close();
    ui->connect->setEnabled(true);
    ui->disConnect->setEnabled(false);
}
