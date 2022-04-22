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
    if(datastr.contains(",")){
        QStringList list = datastr.split(QLatin1Char(','), Qt::SkipEmptyParts);
        Handler::getInstance()->getNames(list[0], list[1]);
    }
    else if(datastr.contains("Who starts")){
        onSendButtonPressed(random_player());
        memory_usage();
    }
    else if(datastr.contains("card")){
        qDebug() << "Position get it";
        parsetosearch(datastr);
        memory_usage();
    }
    else if(datastr.contains("Are equals")){
        string equals = GameLogic::getInstance()->are_equals();
        QString result = QString::fromStdString(equals);
        if(result.contains("YES")){
            onSendButtonPressed(result);
            Handler::getInstance()->update_information();
            Memory::getInstance()->shuffle();
            Handler::getInstance()->update_hits();
            memory_usage();
        }else{
            onSendButtonPressed("NOEQUALS");
            Handler::getInstance()->update_information();
            memory_usage();
        }
    }else{
        Memory::getInstance()->memorymatrix.clear();
        memory_usage();
    }

}

/**
 * @brief MainWindow::parsetosearch
 * @param info
 */

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
 * @brief MainWindow::startGame initializes game components, such as matrix
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
    if(player == 0){
        Handler::getInstance()->turn = Handler::getInstance()->player1;
        return player_number;
    }else{
        Handler::getInstance()->turn = Handler::getInstance()->player2;
        return player_number;
    }

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


/**
 * @brief MainWindow::memory_usage get the used memory information
 */

void MainWindow::memory_usage(){
    int tSize = 0, resident = 0, share = 0;
    ifstream buffer("/proc/self/statm"); //Provides information about memory usage, measured in pages.
    buffer >> tSize >> resident >> share;
    buffer.close();

    long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
    double rss = resident * page_size_kb;
    cout << "RSS - " << rss << " kB\n";

    double shared_mem = share * page_size_kb;
    cout << "Shared Memory - " << shared_mem << " kB" << endl;

    cout << "Private Memory - " << rss - shared_mem << " kB" << endl;

    ui->lblshared->setText(QString::number(shared_mem)+" kB");

    ui->lblprivate->setText(QString::number(rss - shared_mem)+" kB");
}

