#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include "thread"

#pragma once


class TCPServer
{
private:
    int listening;
    int PORT = 5000;
    int clientSocket;
    int bytesReceived;
    sockaddr_in hint;
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    char host[NI_MAXHOST];
    char service[NI_MAXSERV];
    char buf[4096];

    static TCPServer *instance;

public:
    TCPServer();
    void Start();
    void Send(std::string);
    static TCPServer* getInstance();
};

#endif // TCPSERVER_H
