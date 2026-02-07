#ifndef CONNECTION
#define CONNECTION

#include <string>
#include <iostream>
#include <cstring>

#if defined(_WIN32) || defined(_WIN64)

#define WIN32_LEAN_AND_MEAN
#define _WINSOCKAPI_

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

using socket_t = SOCKET;

#else

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using socket_t = int;

#define INVALID_SOCKET (-1)
#define SOCKET_ERROR (-1)
#define closesocket close

#endif

#define SERVER_IP "127.0.0.1"
#define PORT 8080

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <ctime>


class ServerSocket
{
private:
    sockaddr_in servaddr{};
    socket_t sockfd = INVALID_SOCKET;
    int port;
    std::string ip_server;

public:
    std::string name_user;

    ServerSocket(int port, const std::string& ip_server, const std::string& name_user)
        : port(port), ip_server(ip_server), name_user(name_user)
    {
    }
    void savePort(int port) {
        std::string nomeArquivo = "saida.txt";
        std::ofstream arquivo(nomeArquivo);
        arquivo << port;
        arquivo.close();
    }
    void writeLog(const std::string& msg) {
        std::ofstream logFile("plugin.txt", std::ios::app); 
        if (logFile.is_open()) {
            
            std::time_t now = std::time(nullptr);
            char buf[128];
            std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

            logFile << "[" << buf << "] " << msg << "\n";
        }
    }
    bool connectionServer()
    {
#if defined(_WIN32) || defined(_WIN64)
        WSADATA wsaData;
        int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (result != 0) {
            writeLog("WSAStartup falhou com codigo: " + std::to_string(result));
            return false;
        }
#endif

       
        sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (sockfd == INVALID_SOCKET) {
            writeLog("Falha ao criar socket");
            return false;
        }

        
        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(port);

      
        servaddr.sin_addr.s_addr = inet_addr(ip_server.c_str());
        
        if (servaddr.sin_addr.s_addr == INADDR_NONE) {
            writeLog("IP invalido: " + ip_server);
            closesocket(sockfd);
            sockfd = INVALID_SOCKET;
#if defined(_WIN32) || defined(_WIN64)
            WSACleanup();
#endif
            return false;
        }

        std::cout << "Cliente pronto para enviar mensagens ao servidor "
            << ip_server << ":" << port << "\n";
        return true;
    }

    void sendEventServer(const char* msg)
    {
        sendto(sockfd, msg, (int)strlen(msg), 0,
            (sockaddr*)&servaddr, sizeof(servaddr));
    }


    void closeConnection()
    {
        if (sockfd != INVALID_SOCKET)
            closesocket(sockfd);

#if defined(_WIN32) || defined(_WIN64)
        WSACleanup();
#endif
    }
};

#endif
