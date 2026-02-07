#include <plugin.h>
#include <game_sa/CPed.h>
#include <game_sa/CPlayerPed.h>
#include <game_sa/CTimer.h>
#include "../utils/log.h"
#include "events/ProcessEvent.hpp"

using namespace plugin;

class JumpDetectorPlugin
{
private:
    CPed *playerPed;
    ProcessEvent *m_pProcessEvent;
    bool wasAlive;
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
    }

    void Initialize()
    {
        playerPed = FindPlayerPed();

        if (playerPed)
        {

            m_pProcessEvent = new ProcessEvent(playerPed);
            if (m_pProcessEvent)
            {
                m_pProcessEvent->create();
            }
           wasAlive = playerPed->IsAlive();
        }
    }

    void Process()
    {
        m_pProcessEvent->execute();
        if (KeyPressed(VK_F5))
        {
            playerPed->m_fHealth = 0.0f;
            playerPed->m_fMaxHealth = 0.0f;
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