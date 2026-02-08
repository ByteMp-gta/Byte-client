#include "./ProcessEvent.hpp"
#include "./onPlayerJump/onPlayerJump.hpp"
#include "../../utils/log.h"

#if PROCESSEVENT

void ProcessEvent::create()
{
    if (m_cj)
    {
        m_jumpEvent = new CEventOnPlayerJump(m_cj);
        m_deadEvent = new onPlayerDead(m_cj);
        m_damageEvent = new onPlayerDamage(m_cj);
    }
    cjA = nullptr;
}

void ProcessEvent::execute()
{
    m_deadEvent->execute();
    m_damageEvent->execute();
    m_cj = FindPlayerPed();
    static unsigned int frameCounter = 0;
        frameCounter++;

        if (!m_initialized && (frameCounter % 60 == 0))
        {
            CPed *playerPed = FindPlayerPed();
            if (playerPed && !m_jumpEvent)
            {
                m_jumpEvent = new CEventOnPlayerJump(playerPed);
                if (m_jumpEvent)
                {

                    m_initialized = true;
                }
            }
        }

        if (m_jumpEvent && m_jumpEvent->execute())
        {
            m_jumpCount++;

            unsigned int currentTime = CTimer::m_snTimeInMilliseconds;

            if (currentTime - m_lastStatsTime > 5000)
            {
                writeLog("PULO #" + std::to_string(m_jumpCount) + " DETECTADO!");
            }
        }
    
}

ProcessEvent::~ProcessEvent()
{
    if (m_jumpEvent) 
    {
        delete m_jumpEvent;
    }
}
#endif