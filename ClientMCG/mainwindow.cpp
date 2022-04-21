#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostAddress>

MainWindow *MainWindow::instance = nullptr;

MainWindow* MainWindow::getInstance() {
    if (instance == nullptr){
        instance = new MainWindow;
    }
    return instance;
}

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
    startGame();

}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::addplayersname allows to place the names of the players in the game interface
 * @param name1
 * @param name2
 */

void MainWindow::addplayersname(QString name1, QString name2){
    QString player1 = name1;
    QString player2 = name2;
    playername1 = name1;
    playername2 = name2;
    ui->lblname1->setText(player1);
    ui->lblname2->setText(player2);

}


/**
 * @brief MainWindow::startGame initializes game components, such as buttons, scores, and pairs remaining counter
 */

void MainWindow::startGame(){

    first_card = true;

    pairsofcards = 20;

    score1 = 0;

    ui->lblpoints1->setText(QString::number(score1));

    score2 = 0;

    ui->lblpoints2->setText(QString::number(score2));

    ui->frame->setEnabled(false);

    QList<QPushButton *> buttons =  ui->centralwidget->findChildren<QPushButton*>();
       foreach (QPushButton* b, buttons) {
           b->setEnabled(true);
           b->setIcon(QIcon());
    }
}


/**
 * @brief MainWindow::onReadyRead Allows read the messages received by the client socket
 */

void MainWindow::onReadyRead()
{

    const auto data = socket.readAll();
    QString datastr = data;
    QString msg = datastr;
    msg.remove(0,1);
    if(datastr.length()>10){
        if(first_card){
            previousCard=currentCard;
            setimagecard1(datastr,currentCard);
            first_card = false;

        }else{
            setimagecard2(datastr, currentCard);
            first_card = true;
        }

    }else{
        if(datastr.length() < 2){
            start_player(datastr);
        }
        else if(datastr.contains("YESEQUALS")){
            partial_result1();
        }
        else{
            partial_result2();
        }
    }

}

/**
 * @brief MainWindow::start_player
 * @param player
 */

void MainWindow::start_player(QString player){
    ui->frame->setEnabled(true);
    if(player == "0"){
        ui->lblturn->setText(playername1);
    }else{
        ui->lblturn->setText(playername2);
    }
}

/**
 * @brief MainWindow::update_player
 */

void MainWindow::update_player(){
    QString player_turn = ui->lblturn->text();
    if(player_turn == playername1){
        ui->lblturn->setText(playername2);
    }else{
        ui->lblturn->setText(playername1);
    }
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
 * @brief MainWindow::setimagecard changes the image at the first button pressed
 * @param encoded have the image received by the server
 * @param button is the button where the image is changed
 */

void MainWindow::setimagecard1(QString encoded, QPushButton* button){
    QPixmap image;
    image.loadFromData(QByteArray::fromBase64(encoded.toLocal8Bit()));
    if(!image.loadFromData(QByteArray::fromBase64(encoded.toLocal8Bit()))){
        qDebug() << "Error loading the image";
        currentCard->setEnabled(true);
    }else{
        image.loadFromData(QByteArray::fromBase64(encoded.toLocal8Bit()));
        QIcon ButtonIcon;
        ButtonIcon.addPixmap(QPixmap(image),QIcon::Disabled);
        button->setIcon(ButtonIcon);
        button->setIconSize(QSize(60,60));
    }

}

/**
 * @brief MainWindow::setimagecard2 changes the image on the second button pressed and asks if both cards are the same
 * @param encoded have the image received by the server
 * @param button is the button where the image is changed
 */

void MainWindow::setimagecard2(QString encoded, QPushButton* button){
    QPixmap image;
    image.loadFromData(QByteArray::fromBase64(encoded.toLocal8Bit()));
    if(!image.loadFromData(QByteArray::fromBase64(encoded.toLocal8Bit()))){
        qDebug() << "Error loading the image";
        currentCard->setEnabled(true);

    }else{
        image.loadFromData(QByteArray::fromBase64(encoded.toLocal8Bit()));
        QIcon ButtonIcon;
        ButtonIcon.addPixmap(QPixmap(image),QIcon::Disabled);
        button->setIcon(ButtonIcon);
        button->setIconSize(QSize(60,60));
        ui->frame->setEnabled(false);
        onSendButtonPressed("Are equals");
    }

}

/**
 * @brief MainWindow::uncovered_card detect the card that was discovered and send the position to the server
 */

void MainWindow::uncovered_card(){
    currentCard = qobject_cast<QPushButton*>(sender());
    QString position = currentCard->objectName();
    qDebug() << position;
    onSendButtonPressed(position);
    currentCard->setEnabled(false);
}

/**
 * @brief MainWindow::final_result check if all cards were revealed to finish the game
 */

void MainWindow::final_result(){
    msgBox.setWindowTitle("Game over");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    msgBox.setEscapeButton(QMessageBox::No);
    ui->frame->setEnabled(true);
    if(pairsofcards == 0){
        if(score1>score2){
            msgBox.setText("¡You win! " +playername1+  "Final score: " + QString::number(score1) + "\nIt was fun?");
            if (QMessageBox::Yes == msgBox.exec()){
                QCoreApplication::quit();
            }
            else{
                QCoreApplication::quit();
            }
        }else{
            msgBox.setText("¡You win! " +playername2+  "Final score: " + QString::number(score2) + "\nIt was fun?");
            if (QMessageBox::Yes == msgBox.exec()){
                QCoreApplication::quit();
            }
            else{
                QCoreApplication::quit();
            }
        }

    }
    update_player();
}

/**
 * @brief MainWindow::partial_result1 takes appropriate action if the flipped cards are uneven, such as lowering the score
 */

void MainWindow::partial_result1(){
    QString turn = ui->lblturn->text();
    if(turn == playername1){
        score1+=5;
        ui->lblpoints1->setText(QString::number(score1));
    }else{
        score2+=5;
        ui->lblpoints2->setText(QString::number(score2));
    }
    pairsofcards--;
    final_result();
}

/**
 * @brief MainWindow::partial_result2 takes appropriate action if the flipped cards are equal, such as increase the score
 */

void MainWindow::partial_result2(){
    QString turn = ui->lblturn->text();
    if(turn == playername1){
        score1-=2;
        ui->lblpoints1->setText(QString::number(score1));
    }else{
        score2-=2;
        ui->lblpoints2->setText(QString::number(score2));
    }
    QTimer::singleShot(1000, this, SLOT(restartCards()));
}


/**
 * @brief MainWindow::restartCards allows cards to be returned to their previous state if they are not the same
 */

void MainWindow::restartCards(){

    previousCard->setIcon(QIcon());
    currentCard->setIcon(QIcon());

    currentCard->setEnabled(true);
    previousCard->setEnabled(true);

    ui->frame->setEnabled(true);

    update_player();
}



void MainWindow::on_pushButton_clicked(){
    onSendButtonPressed("Who starts");
    ui->pushButton->setEnabled(false);
}

