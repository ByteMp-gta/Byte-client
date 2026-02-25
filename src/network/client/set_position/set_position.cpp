#include "./set_position.hpp"
#include <CVector.h>
#include <plugin.h>
#include <game_sa/CPad.h>
#include "common.h"
#include "CCivilianPed.h"
#include "CWorld.h"
#include "CStreaming.h"
#include "CTaskComplexWanderStandard.h"
#include "CHud.h"
#include "CPopulation.h"
#if SET_POS
void set_position::set(CVector destino, CPed *ped, CVector orintation)
{

    if(ped == nullptr){
        int modelID = 7;
        CStreaming::RequestModel(modelID, 0);
        CStreaming::LoadAllRequestedModels(false);
        ped = new CCivilianPed(CPopulation::IsFemale(modelID) ? PED_TYPE_CIVFEMALE : PED_TYPE_CIVMALE, modelID);
        if (ped)
        {
            ped->SetPosn(destino);
            ped->SetOrientation(orintation.x, orintation.y, orintation.z);
            CWorld::Add(ped);
            ped->PositionAnyPedOutOfCollision();
        }
    }else{
        ped->SetPosn(destino);
        float x,y,z = 0.0f;
        x = orintation.x;
        y = orintation.y;
        z = orintation.z;
        ped->SetOrientation(x,y,z);
    }
    
}
#endif
