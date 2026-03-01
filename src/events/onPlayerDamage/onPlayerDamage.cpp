#include "../../network/connection.hpp"
#include "./onPlayerDamage.hpp"
#include <game_sa/CPlayerPed.h>
#include <plugin.h>
#include "../../../utils/log.h"
#include "../../network/server/onPlayerDamage/onPlayerDamegeServer.hpp"
#include <iostream>
#include <fstream>
#include <string>


#if ONPLAYERDAMAGE
onPlayerDamage::onPlayerDamage(CPed *cj) : cj(cj), wasVida(cj->m_fHealth),
server(server)
{
}

onPlayerDamage::~onPlayerDamage()
{
   
}

void onPlayerDamage::execute()
{
    cj = FindPlayerPed();
     std::ifstream arquivo("name.txt");

    std::string name;
    std::getline(arquivo, name);
    arquivo.close();
    if (cj->IsAlive())
    {
        float dano = wasVida - cj->m_fHealth;
        if (dano > 0.1f )
        {
            onPlayerDamageServer(dano, g_Server, name);
        }
        wasVida = cj->m_fHealth;
    }
}

#endif