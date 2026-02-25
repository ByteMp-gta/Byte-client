#include <CVector.h>
#pragma once
#include <plugin.h>
#include <game_sa/CPad.h>
#define SET_POS 1

#if SET_POS

class set_position {
public:
    static void set(CVector destino, CPed* ped, CVector orintation);
};
#endif