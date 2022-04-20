#include "clientregister.h"
#include "ui_clientregister.h"
#include "mainwindow.h"

ClientRegister::ClientRegister(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientRegister)
{
    ui->setupUi(this);
    connect(this, &ClientRegister::namesignal, this, &ClientRegister::onSignalEmited);
}

ClientRegister::~ClientRegister()
{
    delete ui;
}

/**
 * @brief ClientRegister::onSignalEmited enable the button to start the game upon receiving a signal
 */

void ClientRegister::onSignalEmited(){
    ui->startButton->setEnabled(true);
}

/**
 * @brief ClientRegister::on_startButton_clicked when the button is pressed,
 * it sends the names of the players to the game interface and shows the game interface
 */

void ClientRegister::on_startButton_clicked()
{
    name1 = ui->name1->text();
    name2 = ui->name2->text();
    MainWindow::getInstance()->addplayersname(name1, name2);
    this->close();
    MainWindow::getInstance()->show();

}


/**
 * @brief ClientRegister::on_name1_editingFinished it only prints that the first name was already written
 */

void ClientRegister::on_name1_editingFinished(){
    cout << "First name get it" << endl;
}


/**
 * @brief ClientRegister::on_name2_editingFinished beeps when the second player's name is placed
 * to enable the button to start the game
 */

void ClientRegister::on_name2_editingFinished(){
    emit namesignal();
}


/**
 * @brief ClientRegister::on_name2_returnPressed emits a signal when the name of the second player is entered
 * and enter is pressed, to enable the button to start the game
 */

void ClientRegister::on_name2_returnPressed(){
    emit namesignal();
}

