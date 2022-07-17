#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <qlabel.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_sndBtn_clicked();

    void on_connect_clicked();

    void on_disConnect_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *m_tcp;
    QTcpServer *m_server;
    QLabel *m_status;
    bool connected=false;
};
#endif // MAINWINDOW_H
