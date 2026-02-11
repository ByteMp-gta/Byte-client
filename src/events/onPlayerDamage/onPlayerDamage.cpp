#include "../../network/connection.hpp"
#include "./onPlayerDamage.hpp"
#include <game_sa/CPlayerPed.h>
#include <plugin.h>
#include "../../../utils/log.h"
#include "../../network/server/onPlayerDamage/onPlayerDamegeServer.hpp"

#include <string>


#if ONPLAYERDAMAGE
onPlayerDamage::onPlayerDamage(CPed *cj, ServerSocket* server) : cj(cj), wasVida(cj->m_fHealth),
server(server)
{
}

onPlayerDamage::~onPlayerDamage()
{
   
}

void onPlayerDamage::execute()
{
    cj = FindPlayerPed();
    std::string name = "roberdoo";
    if (cj->IsAlive())
    {
        float dano = wasVida - cj->m_fHealth;
        if (dano > 0.1f )
        {
            onPlayerDamageServer(dano, server, name);
        }
        wasVida = cj->m_fHealth;
    }
}

#endif