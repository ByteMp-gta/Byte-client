#pragma once
#include "../network/connection.hpp"
#include <plugin.h>
#include "./onPlayerJump/onPlayerJump.hpp"
#include "./onPlayerDead/onPlayerDead.hpp"
#include "./onPlayerDamage/onPlayerDamage.hpp"
#include "./onMove/onMove.hpp"
#include <memory>

#define PROCESSEVENT 1

#if PROCESSEVENT

class ProcessEvent {

    private:
        CPed* m_cj;
        CPed* cjA;

        std::unique_ptr<ServerSocket> server;

        std::shared_ptr<CEventOnPlayerJump> m_jumpEvent;
        std::unique_ptr<onPlayerDead> m_deadEvent;
        std::unique_ptr<onPlayerDamage> m_damageEvent;
        std::unique_ptr<onMove> onmove;

        unsigned int m_lastStatsTime;
        int m_jumpCount;
        bool m_initialized;

        
    public:
        ProcessEvent(CPed* cj, ServerSocket* server) : m_cj(cj), m_lastStatsTime(0), m_jumpCount(0), m_initialized(false), server(server) {}
        void execute();
        void create();
        ~ProcessEvent();

};
#endif