#pragma once

#include <game_sa/CPed.h>

#define ONPLAYERJUMP 1

#if ONPLAYERJUMP

class CEventOnPlayerJump {
private:

    CPed* m_cj;
    unsigned int m_lastJumpTime;
    static const unsigned int JUMP_COOLDOWN = 1000; 
    bool m_wasJumping;

public:
    explicit CEventOnPlayerJump(CPed* cj);
    ~CEventOnPlayerJump();
    
    bool execute();
    CPed* getPed() const { return m_cj; }
};

#endif