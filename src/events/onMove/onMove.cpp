#include "../../network/connection.hpp"
#include "./onMove.hpp"
#include <CVector.h>
#include "CPopulation.h"
#include <plugin.h>
#include <fstream>
#include "../../../utils/log.h"
#include <iostream>
#include <string>
#if onMoveDefine

onMove::~onMove() {}

void onMove::run(CPed *cja)
{

    if (!cja)
        return;

    std::ifstream arquivo("name.txt");

    std::string name;
    std::getline(arquivo, name);
    arquivo.close();
    CVector currentPos = cja->GetPosition();

    float currentX, currentY, currentZ;
    cja->GetOrientation(currentX, currentY, currentZ);

    if (!initialized)
    {
        lastPosition = currentPos;
        lastX = currentX;
        lastY = currentY;
        lastZ = currentZ;
        initialized = true;
        return;
    }

    bool posicaoDiferente =
        fabs(currentPos.x - lastPosition.x) > 0.01f ||
        fabs(currentPos.y - lastPosition.y) > 0.01f ||
        fabs(currentPos.z - lastPosition.z) > 0.01f;

    bool orientacaoDiferente =
        fabs(currentX - lastX) > 0.01f ||
        fabs(currentY - lastY) > 0.01f ||
        fabs(currentZ - lastZ) > 0.01f;

    if (posicaoDiferente || orientacaoDiferente)
    {

        if (g_Server)
        {
            std::string msg = "onMovimentPlayer::"+ name + "::" + std::to_string(currentPos.x) + "::" + std::to_string(currentPos.y) + "::" + std::to_string(currentPos.z) + "::" + std::to_string(lastX) + "::" + std::to_string(lastY) + "::" + std::to_string(lastZ);
            g_Server->sendEventServer(msg.c_str());
        }
    }

    // Atualiza estado
    lastPosition = currentPos;
    lastX = currentX;
    lastY = currentY;
    lastZ = currentZ;
}
#endif