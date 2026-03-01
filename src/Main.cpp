#define WIN32_LEAN_AND_MEAN
#include "./network/connection.hpp"
#include "./events/onCheatDetected/onCheatDetected.hpp"
#include "./network/client/set_healh/set_health.hpp"
#include "./network/process_request/Process_request.hpp"
#include <plugin.h>
#include <game_sa/CPed.h>
#include <game_sa/CPlayerPed.h>
#include <game_sa/CTimer.h>
#include "../utils/log.h"
#include "./events/ProcessEvent.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream> 
#include "./global/Name.hpp"


ServerSocket* g_Server = nullptr;
std::string nome = "";
using namespace plugin;

class JumpDetectorPlugin
{
private:
    CPed *playerPed;
    ProcessEvent *m_pProcessEvent;
    bool wasAlive;
    ServerSocket* server;
    CheatDetector* cheat;
    Process_request* process_request;

public:
    JumpDetectorPlugin()
    {
        writeLog("=== JumpDetectorPlugin CONSTRUTOR INICIADO ===");
        
        plugin::Events::gameProcessEvent += [this]()
        {
            this->Process();
        };
        writeLog("gameProcessEvent event handler registrado");

        plugin::Events::initGameEvent += [this]()
        {
            this->Initialize();
        };
        writeLog("initGameEvent event handler registrado");
        
        wasAlive = true;
        server = nullptr;
        cheat = nullptr;
        process_request = nullptr;
        
        writeLog("=== JumpDetectorPlugin CONSTRUTOR FINALIZADO ===\n");
    }

   void Initialize()
   {
       writeLog("\n=== Initialize() INICIADO ===");
       
       playerPed = FindPlayerPed();
       writeLog("FindPlayerPed() executado");
       
       if (playerPed) {
           writeLog("playerPed encontrado: " + toString((void*)playerPed));
       } else {
           writeLog("ERRO: playerPed é NULL!");
       }

       
       writeLog("Tentando ler name.txt...");
       std::ifstream arquivo("name.txt");
       std::string name;
       
       if (!arquivo.is_open()) {
           writeLog("ERRO: Não foi possível abrir name.txt");
           return;
       }
       
       if (!std::getline(arquivo, name) || name.empty()) {
           writeLog("Erro: name.txt vazio ou não encontrado");
           arquivo.close();
           return;
       }
       nome = name;
       arquivo.close();
       writeLog("name.txt lido com sucesso: '" + name + "'");

       // Ler IP
       writeLog("Tentando ler ip.txt...");
       std::ifstream arquivo2("ip.txt");
       std::string ip;
       
       if (!arquivo2.is_open()) {
           writeLog("ERRO: Não foi possível abrir ip.txt");
           return;
       }
       
       if (!std::getline(arquivo2, ip) || ip.empty()) {
           writeLog("Erro: ip.txt vazio ou não encontrado");
           arquivo2.close();
           return;
       }
       arquivo2.close();
       writeLog("ip.txt lido com sucesso: '" + ip + "'");

       // Criar servidor
       writeLog("Criando ServerSocket com PORT=" + toString(PORT) + ", ip=" + ip + ", name=" + name);
       server = new ServerSocket(PORT, ip, name);
       
       if (!server) {
           writeLog("ERRO: Falha ao criar ServerSocket (server é NULL)");
           return;
       }
       writeLog("ServerSocket criado com sucesso");

       writeLog("Chamando server->connectionServer()...");
       if (!server->connectionServer()) {
           writeLog("Falha ao conectar ao servidor " + ip);
           delete server;
           server = nullptr;
           return;
       }
       writeLog("Conexão com servidor estabelecida com sucesso");

       g_Server = server;
       writeLog("g_Server global configurado");

       if (playerPed && server) {
           writeLog("Criando ProcessEvent...");
           m_pProcessEvent = new ProcessEvent(playerPed, server);
           
           if (m_pProcessEvent) {
               writeLog("ProcessEvent criado com sucesso");
               
               std::string eventName = "EU::roobert";
               writeLog("Chamando m_pProcessEvent->create()...");
               m_pProcessEvent->create();
               writeLog("create() executado");
               
               writeLog("Enviando evento ao servidor: '" + eventName + "'");
               server->sendEventServer(eventName.c_str());
               writeLog("Evento enviado");
           } else {
               writeLog("ERRO: Falha ao criar ProcessEvent (m_pProcessEvent é NULL)");
           }

           // Inicializar cheat detector
           writeLog("Criando CheatDetector...");
           
           
           if (cheat) {
               writeLog("CheatDetector criado, chamando update()...");
               cheat->update();
               writeLog("update() executado");
           } else {
               writeLog("ERRO: Falha ao criar CheatDetector");
           }

           writeLog("Criando Process_request...");
           process_request = new Process_request(server);
           
           if (process_request) {
               writeLog("Process_request criado, chamando start()...");
               process_request->start();
               writeLog("start() executado");
           } else {
               writeLog("ERRO: Falha ao criar Process_request");
           }

           wasAlive = playerPed->IsAlive();
           writeLog("wasAlive configurado para: " + toString(wasAlive));
       } else {
           if (!playerPed) writeLog("ERRO: playerPed é NULL, não é possível continuar");
           if (!server) writeLog("ERRO: server é NULL, não é possível continuar");
       }
       
       writeLog("=== Initialize() FINALIZADO ===\n");
   }

    void Process()
    {
        static int processCount = 0;
        processCount++;
        
        // Log a cada 100 execuções para não encher o log
        if (processCount % 100 == 0) {
            writeLog("Process() executado " + toString(processCount) + " vezes");
        }

        if (m_pProcessEvent)
        {
            if (processCount % 100 == 0) {
                writeLog("Executando m_pProcessEvent->execute()");
            }
            m_pProcessEvent->execute();
        } else {
            if (processCount % 100 == 0) {
                writeLog("AVISO: m_pProcessEvent é NULL no Process()");
            }
        }
    }

    ~JumpDetectorPlugin()
    {
        writeLog("\n=== DESTRUTOR INICIADO ===");
        
        if (m_pProcessEvent)
        {
            writeLog("Deletando m_pProcessEvent");
            delete m_pProcessEvent;
            m_pProcessEvent = nullptr;
            writeLog("m_pProcessEvent deletado");
        }
        
        if (server) {
            writeLog("Deletando server");
            delete server;
            server = nullptr;
            writeLog("server deletado");
        }
        
        if (cheat) {
            writeLog("Deletando cheat");
            delete cheat;
            cheat = nullptr;
            writeLog("cheat deletado");
        }
        
        if (process_request) {
            writeLog("Deletando process_request");
            delete process_request;
            process_request = nullptr;
            writeLog("process_request deletado");
        }
        
        writeLog("=== DESTRUTOR FINALIZADO ===\n");
    }
};

JumpDetectorPlugin g_JumpDetector;
