#include "onPlayerJump.hpp"
#include <plugin.h>
#include <game_sa/CTimer.h>
#include <game_sa/CTask.h>
#include "../../../utils/log.h"

#if ONPLAYERJUMP


CEventOnPlayerJump::CEventOnPlayerJump(CPed* cj) 
    : m_cj(cj), m_lastJumpTime(0), m_wasJumping(false) 
{
   
}


CEventOnPlayerJump::~CEventOnPlayerJump() {
    
}


bool CEventOnPlayerJump::execute() {
    if (!m_cj) return false;
    
    unsigned int currentTime = CTimer::m_snTimeInMilliseconds;
    
    
    if (currentTime - m_lastJumpTime < 300) { 
        return false;
    }
    
    bool isJumpingNow = false;
    
    
    for (int i = 0; i < TASK_PRIMARY_MAX; i++) {
    if (!m_cj->m_pIntelligence) continue; 

    CTask* task = m_cj->m_pIntelligence->m_TaskMgr.m_aPrimaryTasks[i];
    if (task) {
        int taskId = task->GetId();
        if (taskId == TASK_SIMPLE_JUMP || taskId == TASK_COMPLEX_JUMP) {
            isJumpingNow = true;
            break;
        }
    }
}

    
    
    if (isJumpingNow && !m_wasJumping) {
        m_wasJumping = true;
        m_lastJumpTime = currentTime;
        
        
       
        return true;
    }
    
    
    if (!isJumpingNow) {
        m_wasJumping = false;
    }
    
    return false;
}

#endif 