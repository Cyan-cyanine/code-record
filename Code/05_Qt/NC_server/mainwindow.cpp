#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Server");
    ui->sendBuf->setDisabled(true);
    ui->port->setText("10086");
    m_server = new QTcpServer(this);
    ui->statusbar->addWidget(new QLabel("连接状态:"));
    m_status = new QLabel();
    ui->statusbar->addWidget(m_status);
    m_status->setPixmap(QPixmap(":/disconnect.png"));
    connect(m_server, &QTcpServer::newConnection, this, [=](){
        m_tcp = m_server->nextPendingConnection();
        ui->histroy->append("连接服务器成功...");
        ui->sendBuf->setEnabled(true);
        connected = true;
        m_status->setPixmap(QPixmap(":/connect.png"));
        connect(m_tcp, &QTcpSocket::readyRead, this, [=](){
            QByteArray tcp_content = m_tcp->readAll();
            ui->histroy->append("客户端:"+tcp_content);
        });
        connect(m_tcp, &QTcpSocket::disconnected, this, [=](){
            ui->histroy->append("已断开连接...");
            connected = false;
            ui->startServer->setEnabled(true);
            m_tcp->deleteLater();
            m_status->setPixmap(QPixmap(":/disconnect.png"));
        });
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_startServer_clicked()
{
    qint16 port = ui->port->text().toUShort();  //端口号
    if(m_server->listen(QHostAddress::Any, port) == false)  //监听
    {
        qDebug("listen error");
        return ;
    }
    ui->startServer->setDisabled(true);
}

void MainWindow::on_sndBtn_clicked()
{
    if(connected)
    {
        QString sndContent = ui->sendBuf->toPlainText();
        ui->histroy->append("服务器:"+sndContent);
        m_tcp->write(sndContent.toUtf8());
        ui->sendBuf->clear();
    }
}
