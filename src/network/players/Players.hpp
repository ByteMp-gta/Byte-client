#ifndef PLAYERS
#define PLAYERS
#include <string>
#include <iostream>
#include <vector>
#include <plugin.h>
#include <game_sa/CPed.h>

class Player{

private:
    int id;
    std::string name;
    CPed* ped;

public:
    Player(std::string name);
    ~Player();
    static CPed* findByUserName(std::string u);

};

extern std::vector<Player> players;

#endif