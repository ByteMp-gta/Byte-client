#include "./Process_request.hpp"
#include "../connection.hpp"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <thread>
#include "../utils/split.hpp"
#include "../players/Players.hpp"
#include <iostream>
#include <fstream>
#include "../client/set_position/set_position.hpp"
#include <plugin.h>

Process_request::Process_request(ServerSocket *server) : server(server)
{
}

void Process_request::filter(std::string msg){
    auto parts = split(msg, "::");
    if(parts[0] == "onMovimentPlayer"){
        
        std::string name1 = parts[1];
        std::ifstream arquivo("name.txt");

        std::string name;
        std::getline(arquivo, name);
        arquivo.close();
        if(name1 == name){
            return ;
        }

        float x = std::stof(parts[2]);
        float y = std::stof(parts[3]);
        float z = std::stof(parts[4]);
        CVector cDirection(x,y,z);
        float ox = std::stof(parts[5]);
        float oy = std::stof(parts[6]);
        float oz = std::stof(parts[7]);
        CVector cOrintacao(ox,oy,oz);
        CPed* ped = Player::findByUserName(name);
        set_position::set(cDirection, ped , cOrintacao);
        return ;
    }

    if(parts[0] == "EU"){
        Player player(parts[1]);
    }

    
}

void Process_request::execute()
{
    char buffer[1024];
    sockaddr_in fromAddr{};
    socklen_t fromLen = sizeof(fromAddr);

    while (true)
    {
        int bytesReceived = recvfrom(server->get_socket_t(), buffer, sizeof(buffer) - 1, 0, (sockaddr *)&fromAddr, &fromLen);
        if (bytesReceived == SOCKET_ERROR)
        {
            std::cerr << "Erro ao receber mensagem\n";
            break;
        }
        buffer[bytesReceived] = '\0';
        std::string msg(buffer);
        filter(msg);
    }
}

void Process_request::start()
{
    std::thread t(&Process_request::execute, this);
    t.detach();
}
Process_request::~Process_request() {}