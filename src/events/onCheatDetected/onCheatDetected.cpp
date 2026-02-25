
#include "onCheatDetected.hpp"
#include "../../network/connection.hpp"
#include <game_sa/CTimer.h>
#include <windows.h>



bool IsModuleLoaded(const char* name)
{
    return GetModuleHandleA(name) != NULL;
}

CheatDetector::CheatDetector()
{
    detected = false;
}

void CheatDetector::update()
{
    static unsigned int lastCheck = 0;

    if (CTimer::m_snTimeInMilliseconds - lastCheck < 3000)
        return;

    lastCheck = CTimer::m_snTimeInMilliseconds;

    if (IsModuleLoaded("cleo.asi") ||
        IsModuleLoaded("moonloader.asi") ||
        IsModuleLoaded("modloader.asi") ||
        IsModuleLoaded("SAMPFUNCS.asi") ||
        IsModuleLoaded("d3d9.dll"))
    {
        if (!detected )
        {
           
            detected = true;
        }
    }
}