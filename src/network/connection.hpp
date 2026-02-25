#ifndef CONNECTION_H
#define CONNECTION_H

#include <string>
#include <iostream>
#include <cstring>
#include <sstream> // Para stringstream

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

// Função auxiliar para converter qualquer tipo para string
template<typename T>
std::string toString(const T& value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

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
        writeLog("=== ServerSocket CONSTRUTOR INICIADO ===");
        writeLog("Porta: " + toString(port));
        writeLog("IP Server: '" + ip_server + "'");
        writeLog("Nome usuário: '" + name_user + "'");
        writeLog("=== ServerSocket CONSTRUTOR FINALIZADO ===\n");
    }

    socket_t get_socket_t(){
        writeLog("get_socket_t() chamado, retornando: " + toString((int)sockfd));
        return sockfd;
    }
    
    void savePort(int port) {
        writeLog("savePort() chamado com porta: " + toString(port));
        std::string nomeArquivo = "saida.txt";
        std::ofstream arquivo(nomeArquivo);
        if (arquivo.is_open()) {
            arquivo << port;
            arquivo.close();
            writeLog("Porta salva em " + nomeArquivo + " com sucesso");
        } else {
            writeLog("ERRO: Não foi possível abrir " + nomeArquivo + " para escrita");
        }
    }
    
    void writeLog(const std::string& msg) {
        std::ofstream logFile("plugin.txt", std::ios::app); 
        if (logFile.is_open()) {
            std::time_t now = std::time(nullptr);
            char buf[128];
            std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

            logFile << "[" << buf << "] " << msg << "\n";
            logFile.close();
        } else {
            // Se não conseguir abrir o arquivo, tenta criar um novo
            std::ofstream newLogFile("plugin.txt");
            if (newLogFile.is_open()) {
                std::time_t now = std::time(nullptr);
                char buf[128];
                std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
                newLogFile << "[" << buf << "] " << msg << "\n";
                newLogFile.close();
            }
        }
    }
    
    bool connectionServer()
    {
        writeLog("\n=== connectionServer() INICIADO ===");
        writeLog("Tentando conectar ao servidor " + ip_server + ":" + toString(port));
        
#if defined(_WIN32) || defined(_WIN64)
        writeLog("Inicializando Winsock...");
        WSADATA wsaData;
        int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (result != 0) {
            writeLog("ERRO: WSAStartup falhou com código: " + toString(result));
            return false;
        }
        writeLog("Winsock inicializado com sucesso. Versão: " + 
                 toString(LOBYTE(wsaData.wVersion)) + "." + 
                 toString(HIBYTE(wsaData.wVersion)));
#endif

        writeLog("Criando socket UDP...");
        sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (sockfd == INVALID_SOCKET) {
            writeLog("ERRO: Falha ao criar socket");
#if defined(_WIN32) || defined(_WIN64)
            int errorCode = WSAGetLastError();
            writeLog("Código do erro Winsock: " + toString(errorCode));
            WSACleanup();
#endif
            return false;
        }
        writeLog("Socket criado com sucesso. Descritor: " + toString((int)sockfd));

        writeLog("Configurando estrutura sockaddr_in...");
        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(port);
        writeLog("Porta configurada: " + toString(port) + " (htons: " + toString(htons(port)) + ")");

        writeLog("Convertendo IP '" + ip_server + "' para formato binário...");
        servaddr.sin_addr.s_addr = inet_addr(ip_server.c_str());
        
        if (servaddr.sin_addr.s_addr == INADDR_NONE) {
            writeLog("ERRO: IP inválido: '" + ip_server + "'");
            closesocket(sockfd);
            sockfd = INVALID_SOCKET;
#if defined(_WIN32) || defined(_WIN64)
            WSACleanup();
#endif
            return false;
        }
        
        // Converte o IP de volta para string para verificar
        char ipStr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(servaddr.sin_addr), ipStr, INET_ADDRSTRLEN);
        writeLog("IP convertido com sucesso: " + std::string(ipStr));

        writeLog("Cliente pronto para enviar mensagens ao servidor " + ip_server + ":" + toString(port));
        writeLog("=== connectionServer() FINALIZADO COM SUCESSO ===\n");
        return true;
    }

    void sendEventServer(const char* msg)
    {
        if (!msg) {
            writeLog("ERRO: sendEventServer recebeu mensagem NULL");
            return;
        }
        
        if (sockfd == INVALID_SOCKET) {
            writeLog("ERRO: sendEventServer - socket inválido");
            return;
        }
        
        size_t msgLen = strlen(msg);
        writeLog("sendEventServer() chamado - Enviando " + toString((int)msgLen) + 
                 " bytes: '" + std::string(msg) + "'");
        
        int sentBytes = sendto(sockfd, msg, msgLen, 0,
            (sockaddr*)&servaddr, sizeof(servaddr));
        
        if (sentBytes == SOCKET_ERROR) {
            writeLog("ERRO: Falha ao enviar mensagem");
#if defined(_WIN32) || defined(_WIN64)
            int errorCode = WSAGetLastError();
            writeLog("Código do erro: " + toString(errorCode));
#endif
        } else {
            writeLog("Mensagem enviada com sucesso. Bytes enviados: " + toString(sentBytes));
        }
    }

    void closeConnection()
    {
        writeLog("\n=== closeConnection() INICIADO ===");
        
        if (sockfd != INVALID_SOCKET) {
            writeLog("Fechando socket " + toString((int)sockfd));
            closesocket(sockfd);
            writeLog("Socket fechado");
        } else {
            writeLog("Socket já estava inválido");
        }

#if defined(_WIN32) || defined(_WIN64)
        writeLog("Limpando Winsock...");
        WSACleanup();
        writeLog("Winsock limpo");
#endif
        writeLog("=== closeConnection() FINALIZADO ===\n");
    }
};

// Declaração externa
extern ServerSocket* g_Server;

// Para debug - escreve no log quando o arquivo é incluído
inline void connection_init_log() {
    std::ofstream logFile("plugin.txt", std::ios::app);
    if (logFile.is_open()) {
        std::time_t now = std::time(nullptr);
        char buf[128];
        std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
        logFile << "[" << buf << "] " << "connection.hpp incluído com sucesso\n";
        logFile.close();
    }
}

// Chama a função de log quando o arquivo é incluído
static bool connection_logged = (connection_init_log(), true);

#endif