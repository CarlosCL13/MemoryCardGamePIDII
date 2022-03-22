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

//Allows messages to be sent over the socket connection from the server class.
void Server::send_message(string msg){
    TCPServer::getInstance()->Send(msg);

}


