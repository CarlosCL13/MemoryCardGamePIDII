#include "client.h"
#include "tcpclient.h"

#include <QApplication>

void RunClient(){

    TCPClient::getInstance()->Start();
    std::cout << "Client Running" << std::endl;
    TCPClient::getInstance()->Send("Todo bien");

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
