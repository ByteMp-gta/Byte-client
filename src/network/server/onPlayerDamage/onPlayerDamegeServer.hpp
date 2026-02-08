#pragma once
#include <string>

#include "../../connection.hpp"

using namespace std;

#define ONPLAYERDAMAGESERVER 1

#if ONPLAYERDAMAGESERVER

void onPlayerDamageServer(float dano, ServerSocket* server, string name);

#endif