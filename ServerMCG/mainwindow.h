#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <iostream>
#include <string>
#include <fstream>
#include "memory.h"
#include <time.h>

//Base64
#include <QBuffer>

#pragma once


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


public slots:
    void onNewConnection();
    void onReadyRead();
    void onStateChanged(QAbstractSocket::SocketState state);
    void onSendButtonPressed(QString msg);
    void startGame();
    QString send_imagebase64(QString type);
    void parsetosearch(QString info);
    QString random_player();
    void update_HF();
    void memory_usage();

private:
    Ui::MainWindow *ui;
    QTcpServer *server;
    QTcpSocket *clientSocket;
    QList<QTcpSocket*> sockets;   

};
#endif // MAINWINDOW_H
