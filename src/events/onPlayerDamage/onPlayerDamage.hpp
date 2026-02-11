#pragma once

#include <plugin.h>
#include "../../network/connection.hpp"

#define ONPLAYERDAMAGE 1

#if ONPLAYERDAMAGE

class onPlayerDamage {
private:
    CPed* cj;
    ServerSocket* server;
    float wasVida;
public:
    explicit onPlayerDamage(CPed* cj, ServerSocket* server);
    ~onPlayerDamage();
    void execute();
};

#endif