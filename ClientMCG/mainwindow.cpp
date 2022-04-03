#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostAddress>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      socket(this)
{
    ui->setupUi(this);
    socket.connectToHost(QHostAddress("127.0.0.1"), 9999);
    connect(&socket,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onReadyRead()
{
    //QByteArray data = socket.readAll();
    //qDebug() << data;
    //QString::fromStdString(data.toStdString());
    const auto data = socket.readAll();
    string base = data.toStdString();

    setimagecard(base);

    string datastr = data.toStdString();
    cout << datastr << endl;


}
void MainWindow::onSendButtonPressed(QString message)
{
    qDebug() << "onSendButtonPressed";
    QString text = message;
    socket.write(QByteArray::fromStdString(text.toStdString()));
}

void MainWindow::setimagecard(string encoded){
    //cout << "paso" << endl;
    //std::string imgencoded = encoded.erase(encoded.find("img"));

    QString qencoded = QString::fromStdString(encoded);
    QPixmap image;
    image.loadFromData(QByteArray::fromBase64(qencoded.toLocal8Bit()));
    QIcon ButtonIcon(image);
    ui->card1->setIcon(ButtonIcon);
    ui->card1->setIconSize(QSize(190,390));
}




void MainWindow::on_card1_clicked()
{
    onSendButtonPressed("img1");
}



void MainWindow::on_card2_clicked()
{
    onSendButtonPressed("img2");

}

