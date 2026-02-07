#include "log.h"
#include <fstream>
#include <string>
#include <ctime>

void writeLog(const std::string& msg) {
     // Abrir arquivo de log
    std::ofstream logFile("JumpPlugin.log", std::ios::app);
    
    if (logFile.is_open()) {
        // Tempo atual
        std::time_t now = std::time(nullptr);
        char timeStr[64];
        std::strftime(timeStr, sizeof(timeStr), "[%H:%M:%S]", std::localtime(&now));
        
        // Escrever
        logFile << timeStr << " " << msg << std::endl;
        logFile.close();
    }
    
    // Debug output
    OutputDebugStringA(("[JUMP] " + msg + "\n").c_str());
}