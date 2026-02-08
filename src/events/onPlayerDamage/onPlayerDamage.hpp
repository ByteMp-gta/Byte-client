#pragma once

#include <plugin.h>

#define ONPLAYERDAMAGE 1

#if ONPLAYERDAMAGE

class onPlayerDamage {
private:
    CPed* cj;
    float wasVida;
public:
    explicit onPlayerDamage(CPed* cj);
    ~onPlayerDamage();
    void execute();
};

#endif