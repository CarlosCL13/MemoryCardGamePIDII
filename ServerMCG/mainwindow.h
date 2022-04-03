#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <iostream>
#include <fstream>

//Base64
#include <QBuffer>


using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    static MainWindow *instance;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static MainWindow* getInstance();

    void send_imagebase64();

public slots:
    void onNewConnection();
    void onReadyRead();
    void onStateChanged(QAbstractSocket::SocketState state);
    void onSendButtonPressed(QString msg);

private slots:
    void on_pushButton_clicked();

    void on_prueba_clicked();

private:
    Ui::MainWindow *ui;
    QTcpServer *server;
    QTcpSocket *clientSocket;
    QList<QTcpSocket*> sockets;   

};
#endif // MAINWINDOW_H
