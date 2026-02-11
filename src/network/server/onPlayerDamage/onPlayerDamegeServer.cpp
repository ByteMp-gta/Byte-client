#include "./onPlayerDamegeServer.hpp"
#include "../../connection.hpp"
#include <string>
#include "../../../../utils/log.h"

using namespace std;

#if ONPLAYERDAMAGESERVER


void onPlayerDamageServer(float dano, ServerSocket* server, string name)
{
    string str = string("onPlayerDamage::") + name + "::"+to_string(dano);
    server->sendEventServer(str.c_str());
    writeLog("aqui passou !");

}

#endif