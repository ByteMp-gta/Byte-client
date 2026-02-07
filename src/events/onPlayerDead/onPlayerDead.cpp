#include "./onPlayerDead.hpp"
#include <plugin.h>
#include "../../../utils/log.h"


onPlayerDead::onPlayerDead(CPed* cj): cj(cj), wasAlive(cj->IsAlive()){}

onPlayerDead::~onPlayerDead(){

}

void  onPlayerDead::execute(){
    
   cj = FindPlayerPed();
        if(cj){
            bool isAliveNow = cj->IsAlive();
            
            if(wasAlive && !isAliveNow)
            {
                writeLog("Player esta morto");
            }
            wasAlive = isAliveNow;
        }
}
