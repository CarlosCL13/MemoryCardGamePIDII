#include "client.h"
#include "tcpclient.h"

#include <QApplication>

//Allows to start the execution of the client by instantiating it
void RunClient(){

    TCPClient::getInstance()->Start();
    std::cout << "Client Running" << std::endl;

}

int main(int argc, char *argv[])
{
    std::thread RunC (RunClient);

    QApplication a(argc, argv);
    Client w;
    w.show();
    return a.exec();

    RunC.join();
}
