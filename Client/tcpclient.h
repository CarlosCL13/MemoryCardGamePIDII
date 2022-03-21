#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <thread>


class TCPClient
{
private:
    int sock;
    int port = 5000;
    int connectRes;
    sockaddr_in hint;
    std::string ipAddress = "127.0.0.1";
    char buf[4092];
    static TCPClient *instance;
    TCPClient() = default;

public:
    static TCPClient* getInstance();
    void Start();
    void Send(std::string);
};

#endif // TCPCLIENT_H
