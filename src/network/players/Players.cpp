#include "./Players.hpp"
#include <iostream>
#include <vector>
#include <plugin.h>
#include <string>

std::vector<Player> players;

Player::Player(std::string name) : name(name), ped(nullptr)
{

    if (!name.empty())
    {
        Player player_anterior = players.back();
        id = player_anterior.id + 1;
        players.push_back(*this);
        return;
    }
    id = 0;
    players.push_back(*this);
}

CPed *Player::findByUserName(std::string u)
{
    if(players.empty()){ return nullptr;}

    for(Player p : players){
        if(p.name == u){
            return p.ped;
        }
    }
}

Player::~Player() {}