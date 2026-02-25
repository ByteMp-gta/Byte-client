#ifndef PROCESS_REQUEST
#define PROCESS_REQUEST
#include "../connection.hpp"

class Process_request
{

private:
   ServerSocket* server; 
   void execute();    
   void filter(std::string msg);

public:
    Process_request(ServerSocket* server);
    ~Process_request();
    void start();
};



#endif