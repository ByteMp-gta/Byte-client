#pragma once 
#include <CVector.h>
#include <plugin.h>
#include <game_sa/CPed.h>
#define onMoveDefine 1

#if onMoveDefine

class onMove{
    
private:
    CPed *cj;
    CVector vector;
    CVector lastPosition;
    float lastX, lastY, lastZ;
    bool initialized = false;

public:
    explicit onMove(CPed *cj):cj(cj), vector(cj->GetPosition()){};

    ~onMove();

    void run(CPed *cja);

};

#endif