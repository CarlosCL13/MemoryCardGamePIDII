#include "server.h"
#include "tcpserver.h"
#include "./ui_server.h"

Server::Server(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Server)
{
    ui->setupUi(this);
}

Server::~Server()
{
    delete ui;
}

void Server::send_message(string msg){
    TCPServer::getInstance()->Send(msg);

}

void Server::on_pushButton_clicked()
{
    send_message("si funca");
}

