#include <plugin.h>
#include <game_sa/CPed.h>
#include <game_sa/CPlayerPed.h>
#include <game_sa/CTimer.h>
#include "../utils/log.h"
#include "events/ProcessEvent.hpp"
#include "./network/connection.hpp"

using namespace plugin;

class JumpDetectorPlugin
{
private:
    CPed *playerPed;
    ProcessEvent *m_pProcessEvent;
    bool wasAlive;
    ServerSocket* server;

    

public:
    JumpDetectorPlugin()
    {

        plugin::Events::gameProcessEvent += [this]()
        {
            this->Process();
        };

        plugin::Events::initGameEvent += [this]()
        {
            this->Initialize();
        };
        wasAlive = true;
        server = nullptr;
    }

    void Initialize()
    {
        playerPed = FindPlayerPed();
        server = new ServerSocket(PORT, SERVER_IP, "roberdoo");

        if (playerPed && server)
        {

            m_pProcessEvent = new ProcessEvent(playerPed, server);
            if (m_pProcessEvent)
            {
                m_pProcessEvent->create();
            }
            wasAlive = playerPed->IsAlive();
            
        }
    }

    void Process()
    {
        

        if (m_pProcessEvent)
        {
            m_pProcessEvent->execute();
        }
    }
    

    ~JumpDetectorPlugin()
    {

        if (m_pProcessEvent)
        {
            delete m_pProcessEvent;
            m_pProcessEvent = nullptr;
        }
    }
};

// Instância global do plugin
JumpDetectorPlugin g_JumpDetector;