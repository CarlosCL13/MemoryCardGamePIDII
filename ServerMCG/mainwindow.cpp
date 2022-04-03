#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow *MainWindow::instance = nullptr;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    qDebug() << "Constructor";
    ui->setupUi(this);
    server = new QTcpServer(this);
    server->listen(QHostAddress::Any, 9999);
    clientSocket=new QTcpSocket(this);
    // Connect to slot
    connect(server, SIGNAL(newConnection()),this,SLOT(onNewConnection()));
}

MainWindow* MainWindow::getInstance() {
    if (instance == nullptr){
        instance = new MainWindow;
    }
    return instance;
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::onNewConnection()
{
    qDebug() << "onNewConnection";
    clientSocket=server->nextPendingConnection();
    // Ready read
        connect(clientSocket, SIGNAL(readyRead()),this,SLOT(onReadyRead()));
    // State Changed
        connect(clientSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this,SLOT(onStateChanged(QAbstractSocket::SocketState)));

    sockets.push_back(clientSocket);
}


void MainWindow::onStateChanged(QAbstractSocket::SocketState state)
{
    qDebug() << "onStateChanged";
    if (state == QAbstractSocket::UnconnectedState){
        QTcpSocket* s = static_cast<QTcpSocket*>(QObject::sender());
        sockets.removeOne(s);
    }
}


void  MainWindow::onReadyRead()
{
    qDebug() << "onReadyRead";

    QTcpSocket* s = static_cast<QTcpSocket*>(QObject::sender());
    /*QByteArray data = s->readAll();
    QString::fromStdString(data.toStdString());
    cout << data.toStdString() << endl;
    onSendButtonPressed("que tal");*/
    const auto data = s->readAll();
    string msg = data.toStdString();
    if(msg=="img1"){
        send_imagebase64();
    }
    else if(msg=="img2"){
        qDebug() << QString::fromStdString(data.toStdString());
    }
    //qDebug() << QString::fromStdString(data.toStdString());
    /*for (QTcpSocket* socket : sockets){
        socket ->write(data);
    }*/

}

void MainWindow::send_imagebase64(){
    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    QPixmap qp(":/github.png");
    qp.save(&buffer, "PNG");
    QString encoded = buffer.data().toBase64();
    string encodedstr = encoded.toStdString();
    //cout << "se envia" << endl;
    onSendButtonPressed(encoded);
}

void MainWindow::onSendButtonPressed(QString msg)
{
    qDebug() << "onSendButtonPressed";
    QString text = msg;
    clientSocket->write(msg.toUtf8());
    clientSocket->flush();
}

void MainWindow::on_pushButton_clicked()
{
    send_imagebase64();
}


void MainWindow::on_prueba_clicked()
{
    //TCPServer::getInstance()->Send("me quieres?");
}

