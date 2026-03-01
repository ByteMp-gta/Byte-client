
#ifndef HOOK_BASE
#define HOOK_BASE

#include <plugin.h>

class hook_base
{
private:
    CPed* cj;
public:
    hook_base();
    ~hook_base();
    void run();
};




#endif