#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "virtualmemory.h"
#include "memory.h"
#include "gamelogic.h"
#include "handler.h"

MainWindow *MainWindow::instance = nullptr;

MainWindow* MainWindow::getInstance() {
    if (instance == nullptr){
        instance = new MainWindow;
    }
    return instance;
}

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
    startGame();

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

void MainWindow::onReadyRead()
{
    qDebug() << "onReadyRead";
    QTcpSocket* s = static_cast<QTcpSocket*>(QObject::sender());
    const auto data = s->readAll();
    QString datastr = data;
    /*Handler::getInstance()->messagehandler(datastr);
    while(true){
        if(messagetosend != ""){
        this->onSendButtonPressed(messagetosend);
        break;
       }
    }*/
    if(datastr.contains("Who starts")){
        onSendButtonPressed(random_player());
    }
    if(datastr.contains("card")){
        qDebug() << "Position get it";
        parsetosearch(datastr);
    }
    if(datastr.contains("Are equals")){
        string equals = GameLogic::getInstance()->are_equals();
        if(equals == "YES"){
            onSendButtonPressed("YESEQUALS");
            Memory::getInstance()->erasecardinmemory(GameLogic::getInstance()->position1);
            Memory::getInstance()->erasecardinmemory(GameLogic::getInstance()->position2);
            GameLogic::getInstance()->position1 = "";
            GameLogic::getInstance()->position2 = "";
        }else{
            onSendButtonPressed("NOEQUALS");
            Memory::getInstance()->erasecardinmemory(GameLogic::getInstance()->position1);
            Memory::getInstance()->erasecardinmemory(GameLogic::getInstance()->position2);
            GameLogic::getInstance()->position1 = "";
            GameLogic::getInstance()->position2 = "";
        }
    }

}

void MainWindow::parsetosearch(QString info){
    QString position = info.remove(0,4);
    position.insert(1,":");
    string pos = position.toStdString();
    string card = GameLogic::getInstance()->getType(pos);
    cout << "The card is: " + card << endl;
    QString image = send_imagebase64(QString::fromStdString(card));
    onSendButtonPressed(image);
    update_HF();
}

/**
 * @brief MainWindow::send_imagebase64 allows send the image in base64
 */

QString MainWindow::send_imagebase64(QString type){
    QString typecard = type;
    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    QPixmap qp(":/"+typecard+".png");
    qp.save(&buffer, "PNG");
    QString encoded = buffer.data().toBase64();
    string encodedstr = encoded.toStdString();
    //cout << "se envia" << endl;
    //onSendButtonPressed(card_number+encoded);
    QString information = encoded;
    return information;

}

/**
 * @brief MainWindow::onSendButtonPressed allows send messages at the client
 * @param msg
 */

void MainWindow::onSendButtonPressed(QString msg)
{
    qDebug() << "onSendButtonPressed";
    clientSocket->write(msg.toUtf8());
    clientSocket->flush();
}

/**
 * @brief MainWindow::startGame initializes game components, such as matrix, scores, and pairs remaining counter
 */

void MainWindow::startGame(){

    VirtualMemory::getInstance()->generate_matrix();

    Memory::getInstance()->start_matrix();

}

/**
 * @brief MainWindow::random_player
 */

QString MainWindow::random_player(){
    int player;
    srand(time(NULL));
    player = rand()%2;
    QString player_number = QString::number(player);
    return player_number;
}

void MainWindow::update_message(){
    Handler::getInstance()->setmessagetosend(ptrmessagetosend);

}

/**
 * @brief MainWindow::update_HF
 */

void MainWindow::update_HF(){
    int hits = Memory::getInstance()->pagehits;
    int faults = Memory::getInstance()->pagefaults;
    QString pageh = QString::number(hits);
    QString pagef = QString::number(faults);
    ui->lblhits->setText(pageh);
    ui->lblfaults->setText(pagef);

}
