//
// Created by tobias on 2023-10-27.
//

#ifndef COMMS_HELPERS_H
#define COMMS_HELPERS_H

#include "client.h"
#include "server.h"
#include <string>

void start_server(std::string addr, int port);
void start_client(std::string addr, int port);
std::string get_input();
void error(const char *msg);

#endif //COMMS_HELPERS_H
