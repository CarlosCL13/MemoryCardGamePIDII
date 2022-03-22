#include "tcpclient.h"

TCPClient *TCPClient::instance = nullptr;

/**
 * Method to get the instance of the Client class, since it is a singleton.
 * @return
 */
TCPClient* TCPClient::getInstance() {
    if (instance == nullptr){
        instance = new TCPClient;
    }
    return instance;
}

/**
 * Method to start executing the client and keep it running constantly receiving what comes from the server.
 * Performs processes as they are received, connects with the UI to access all its functions.
 */
void TCPClient::Start() {

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1){
        exit(1);
    }

    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    //	Connect to the server on the socket
    connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
    if (connectRes == -1)
    {
        exit(1);
    }

    TCPClient::getInstance()->Send("hola");

    bool run = true;
    while (run){
        memset(buf, 0, 4096);
        int bytesReceived = recv(sock, buf, 4096, 0);
        if (bytesReceived == -1)
        {
            std::cout << "Error getting response" << std::endl;
        }
        else {

            //		Display response
            std::string received = std::string(buf, bytesReceived);

            std::cout << "From Server:" << std::string(buf, bytesReceived) << std::endl;
        }
    }
    close(sock);
    exit(0);
}

//Allows send information to the server
using namespace std::literals::chrono_literals;
void TCPClient::Send(std::string msg) {
    std::this_thread::sleep_for(0.15s);
    int sendRes = send(sock, msg.c_str(), msg.length(), 0);
    if (sendRes == -1) {
        std::cout << "Send message failed" << std::endl;
    }
}
