#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "virtualmemory.h"

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
    VirtualMemory::getInstance()->generate_matrix();
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

/**
 * @brief MainWindow::onNewConnection allows the connection with the client
 */
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

/**
 * @brief MainWindow::onStateChanged verifies the state of the server connections
 * @param state
 */
void MainWindow::onStateChanged(QAbstractSocket::SocketState state)
{
    qDebug() << "onStateChanged";
    if (state == QAbstractSocket::UnconnectedState){
        QTcpSocket* s = static_cast<QTcpSocket*>(QObject::sender());
        sockets.removeOne(s);
    }
}


/**
 * @brief MainWindow::onReadyRead allows read the messages received
 */

void  MainWindow::onReadyRead()
{
    qDebug() << "onReadyRead";

    QTcpSocket* s = static_cast<QTcpSocket*>(QObject::sender());
    /*QByteArray data = s->readAll();
    QString::fromStdString(data.toStdString());
    cout << data.toStdString() << endl;
    onSendButtonPressed("que tal");*/
    const auto data = s->readAll();
    QString datastr = data;
    QString msg = datastr;
    msg.remove(0,1);

    if(datastr.contains("card")){
        qDebug() << "Position get it";
        QString position = datastr.remove(0,4);
        position.insert(1,":");
        string pos = position.toStdString();
        string card = VirtualMemory::getInstance()->getCard(pos);
        card.erase(0,1);
        cout << "The card is: " + card << endl;
        send_imagebase64(QString::fromStdString(card));
    }

    //qDebug() << QString::fromStdString(data.toStdString());
    /*for (QTcpSocket* socket : sockets){
        socket ->write(data);
    }*/

}

/**
 * @brief MainWindow::send_imagebase64 allows send the image in base64
 */


void MainWindow::send_imagebase64(QString type){
    QString typecard = type;
    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    QPixmap qp(":/"+typecard+".png");
    qp.save(&buffer, "PNG");
    QString encoded = buffer.data().toBase64();
    string encodedstr = encoded.toStdString();
    //cout << "se envia" << endl;
    onSendButtonPressed(encoded);
}

/**
 * @brief MainWindow::onSendButtonPressed allows send messages at the client
 * @param msg
 */

void MainWindow::onSendButtonPressed(QString msg)
{
    qDebug() << "onSendButtonPressed";
    QString text = msg;
    clientSocket->write(msg.toUtf8());
    clientSocket->flush();
}



void MainWindow::on_pushButton_clicked()
{
    //send_imagebase64();
    onSendButtonPressed("NHola que tal");
}



void MainWindow::on_prueba_clicked()
{
    string carta =VirtualMemory::getInstance()->getCard("3:9");
    QString qcarta = QString::fromStdString(carta);
    qDebug() << qcarta.remove(0,1);

}

