#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostAddress>

MainWindow *MainWindow::instance = nullptr;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      socket(this)
{
    ui->setupUi(this);
    socket.connectToHost(QHostAddress("127.0.0.1"), 9999);
    connect(&socket,SIGNAL(readyRead()),this,SLOT(onReadyRead()));

    connect(ui->card00, SIGNAL(clicked()), this, SLOT(uncovered_card()));
    connect(ui->card01, SIGNAL(clicked()), this, SLOT(uncovered_card()));
    connect(ui->card02, SIGNAL(clicked()), this, SLOT(uncovered_card()));
    connect(ui->card03, SIGNAL(clicked()), this, SLOT(uncovered_card()));
    connect(ui->card04, SIGNAL(clicked()), this, SLOT(uncovered_card()));
    connect(ui->card05, SIGNAL(clicked()), this, SLOT(uncovered_card()));
    connect(ui->card06, SIGNAL(clicked()), this, SLOT(uncovered_card()));
    connect(ui->card07, SIGNAL(clicked()), this, SLOT(uncovered_card()));
    connect(ui->card08, SIGNAL(clicked()), this, SLOT(uncovered_card()));
    connect(ui->card09, SIGNAL(clicked()), this, SLOT(uncovered_card()));
    connect(ui->card10, SIGNAL(clicked()), this, SLOT(uncovered_card()));
    connect(ui->card11, SIGNAL(clicked()), this, SLOT(uncovered_card()));
    connect(ui->card12, SIGNAL(clicked()), this, SLOT(uncovered_card()));
    connect(ui->card13, SIGNAL(clicked()), this, SLOT(uncovered_card()));
    connect(ui->card14, SIGNAL(clicked()), this, SLOT(uncovered_card()));
    connect(ui->card15, SIGNAL(clicked()), this, SLOT(uncovered_card()));
    connect(ui->card16, SIGNAL(clicked()), this, SLOT(uncovered_card()));
    connect(ui->card17, SIGNAL(clicked()), this, SLOT(uncovered_card()));
    connect(ui->card18, SIGNAL(clicked()), this, SLOT(uncovered_card()));
    connect(ui->card19, SIGNAL(clicked()), this, SLOT(uncovered_card()));
    connect(ui->card20, SIGNAL(clicked()), this, SLOT(uncovered_card()));
    connect(ui->card21, SIGNAL(clicked()), this, SLOT(uncovered_card()));
    connect(ui->card22, SIGNAL(clicked()), this, SLOT(uncovered_card()));
    connect(ui->card23, SIGNAL(clicked()), this, SLOT(uncovered_card()));
    connect(ui->card24, SIGNAL(clicked()), this, SLOT(uncovered_card()));
    connect(ui->card25, SIGNAL(clicked()), this, SLOT(uncovered_card()));
    connect(ui->card26, SIGNAL(clicked()), this, SLOT(uncovered_card()));
    connect(ui->card27, SIGNAL(clicked()), this, SLOT(uncovered_card()));
    connect(ui->card28, SIGNAL(clicked()), this, SLOT(uncovered_card()));
    connect(ui->card29, SIGNAL(clicked()), this, SLOT(uncovered_card()));
    connect(ui->card30, SIGNAL(clicked()), this, SLOT(uncovered_card()));
    connect(ui->card31, SIGNAL(clicked()), this, SLOT(uncovered_card()));
    connect(ui->card32, SIGNAL(clicked()), this, SLOT(uncovered_card()));
    connect(ui->card33, SIGNAL(clicked()), this, SLOT(uncovered_card()));
    connect(ui->card34, SIGNAL(clicked()), this, SLOT(uncovered_card()));
    connect(ui->card35, SIGNAL(clicked()), this, SLOT(uncovered_card()));
    connect(ui->card36, SIGNAL(clicked()), this, SLOT(uncovered_card()));
    connect(ui->card37, SIGNAL(clicked()), this, SLOT(uncovered_card()));
    connect(ui->card38, SIGNAL(clicked()), this, SLOT(uncovered_card()));
    connect(ui->card39, SIGNAL(clicked()), this, SLOT(uncovered_card()));

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

void MainWindow::addplayersname(QString name1, QString name2){
    QString player1 = name1;
    QString player2 = name2;
    ui->lblname1->setText(player1);
    ui->lblname2->setText(player2);
}


/**
 * @brief MainWindow::onReadyRead Allows read the messages received by the client socket
 */

void MainWindow::onReadyRead()
{
    //QByteArray data = socket.readAll();
    //qDebug() << data;
    //QString::fromStdString(data.toStdString());
    /*string base = data.toStdString();

    setimagecard(base);*/

    const auto data = socket.readAll();
    QString datastr = data;
    string img = datastr.toStdString();
    QString msg = datastr;
    msg.remove(0,1);
    setimagecard(img,currentCard);

    //N=message

    /*if(datastr.contains("N")){
        qDebug() << msg;
    }else{
        cout << "imagen recibidad" << endl;
    }*/
//Probar que funcione lo de recibir la imagen


}


/**
 * @brief MainWindow::onSendButtonPressed Allow send messages at the server
 * @param message have the text that will be send
 */

void MainWindow::onSendButtonPressed(QString message)
{
    qDebug() << "onSendButtonPressed";
    QString text = message;
    socket.write(QByteArray::fromStdString(text.toStdString()));
}

/**
 * @brief MainWindow::setimagecard Change the image at the button pressed
 * @param encoded have the image received by the server
 */

void MainWindow::setimagecard(string encoded, QPushButton* button){
    //cout << "paso" << endl;
    //std::string imgencoded = encoded.erase(encoded.find("img"));

    QString qencoded = QString::fromStdString(encoded);
    QPixmap image;
    image.loadFromData(QByteArray::fromBase64(qencoded.toLocal8Bit()));
    QIcon ButtonIcon(image);
    /*ui->card00->setIcon(ButtonIcon);
    ui->card00->setIconSize(QSize(60,60));*/
    button->setIcon(ButtonIcon);
    button->setIconSize(QSize(60,60));
}

void MainWindow::uncovered_card(){
    currentCard = qobject_cast<QPushButton*>(sender());
    QString position = currentCard->objectName();
    qDebug() << position;
    onSendButtonPressed(position);
}




