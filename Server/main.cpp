#include "server.h"
#include <iostream>
#include "tcpserver.h"

#include <QApplication>

//Allows to start the execution of the server by instantiating it
void RunServer(){

    std::cout << "Server Running" << std::endl;
    TCPServer::getInstance()->Start();

}

int main(int argc, char *argv[])
{
    std::thread RunS (RunServer);

    QApplication a(argc, argv);
    Server w;
    w.show();
    return a.exec();

    RunS.join();


    return 0;
}
