#include "tcpclient.h"

TCPClient *TCPClient::instance = nullptr;

/**
 * @brief Metodo para obtener la insrtancia de la clase Client, ya que es un singleton.
 * @return
 */
TCPClient* TCPClient::getInstance() {
    if (instance == nullptr){
        instance = new TCPClient;
    }
    return instance;
}

/**
 * Metodo para empezar a correr el cliente y se mantiene corriendo constantemente recibiendo lo que provenga del server.
 * Realiza procesos segun lo recibido, conecta con GUI para acceder a todas sus funciones.
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

/*Envia los mensajes*/
using namespace std::literals::chrono_literals;
void TCPClient::Send(std::string msg) {
    std::this_thread::sleep_for(0.15s);
    int sendRes = send(sock, msg.c_str(), msg.length(), 0);
    if (sendRes == -1) {
        std::cout << "Send message failed" << std::endl;
    }
}
