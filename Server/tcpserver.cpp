#include "tcpserver.h"
#include <iostream>
#include "string"
#include "stdio.h"

TCPServer *TCPServer::instance = nullptr;

/**
 * Constructor to avoid instantiation.
 */
TCPServer::TCPServer() {}

/**
 * Method to get the instance from the server, since there can only be one instance.
 * @return
 */
TCPServer* TCPServer::getInstance() {
    if (instance == nullptr){
        instance = new TCPServer;
    }
    return instance;
}

/**
 * Method that is responsible for starting the server and keeping it open and listening for any message from the client,
 * it only acts when it receives messages.
 */
void TCPServer::Start() {
    listening = socket(AF_INET, SOCK_STREAM,0);
    if (listening == -1)
    {
        std::cerr << "Can't create a socket! Quitting" << std::endl;
        exit(-1);
    }

    hint.sin_family = AF_INET;
    hint.sin_port = htons(PORT);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

    bind(listening, (sockaddr*)&hint, sizeof(hint));

    // Tell Winsock the socket is for listening
    listen(listening, SOMAXCONN);

    clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

    memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXSERV);

    if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
    {
        std::cout << host << " connected on port " << service << std::endl;
    }
    else
    {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        std::cout << host << " connected on port " << ntohs(client.sin_port) << std::endl;
    }



    // Close listening socket
    close(listening);

    while (true)
    {
        memset(buf, 0, 4096);

        // Wait for client to send data
        bytesReceived = recv(clientSocket, buf, 4096, 0);
        if (bytesReceived == -1)
        {
            std::cerr << "Error in recv(). Quitting" << std::endl;
            break;
        }

        if (bytesReceived == 0)
        {
            std::cout << "Client disconnected " << std::endl;
            break;
        }

        std::string received = std::string(buf,bytesReceived);
        std::cout << buf << std::endl;

    }

    close(clientSocket);
}

//Allows send information to the client
using namespace std::literals::chrono_literals;
void TCPServer::Send(std::string msg) {
    std::this_thread::sleep_for(0.25s);
    send(clientSocket, msg.c_str(), strlen(msg.c_str()) , 0);
}

