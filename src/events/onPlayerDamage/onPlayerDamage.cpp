#include "./onPlayerDamage.hpp"
#include <game_sa/CPlayerPed.h>
#include <plugin.h>
#include "../../../utils/log.h"

#if ONPLAYERDAMAGE
onPlayerDamage::onPlayerDamage(CPed *cj) : cj(cj), wasVida(cj->m_fHealth)
{
}

onPlayerDamage::~onPlayerDamage()
{
   
}

void onPlayerDamage::execute()
{
    cj = FindPlayerPed();
    if (cj->IsAlive())
    {
        float dano = wasVida - cj->m_fHealth;
        if (dano > 0.1f )
        {
            writeLog("Player tomou " + std::to_string(dano) + " de dano");
        }
        wasVida = cj->m_fHealth;
    }
}

#endif