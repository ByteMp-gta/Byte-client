#include "./set_health.hpp"
#include <plugin.h>
#include <game_sa/CTimer.h>
#if SETHEALTH

void set_health(float health)
{

    CPed* playerPed = FindPlayerPed();
   
    playerPed->m_fHealth = 50.0f;

    
    *(int *)((DWORD)playerPed + 0x530) = 1;

    
    DWORD pPlayerData = *(DWORD *)0xB7CD98;
    if (pPlayerData)
    {
       
        *(BYTE *)(pPlayerData + 0x3) = 0;
    }
}

#endif