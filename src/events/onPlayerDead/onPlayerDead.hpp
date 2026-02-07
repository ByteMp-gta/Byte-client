#pragma once

#include <game_sa/CPed.h>

#define ONPLAYERDEAD 1

#if ONPLAYERDEAD

class onPlayerDead{    
private:
    CPed* cj;
    bool wasAlive;

public:
    explicit onPlayerDead(CPed* cj);
    void execute();
    ~onPlayerDead();
};

#endif
