//
// Created by tobias on 2023-10-27.
//

#include <iostream>
#include <utility>
#include "helpers.h"
#include "server.h"
#include "client.h"

void start_server(std::string addr, int port){
    std::cout << "Starting server##" << std::endl;
    server s = server(std::move(addr), port);
    s.start_listen();
}

void start_client(std::string addr, int port){
    std::cout << "Starting client##" << std::endl;
    client c;
    c = client(std::move(addr), port);
    int err = c.start_listen();
    if (err < 0)
    {
        std::cout << "Error in clients listen function" << std::endl;
    }
}

std::string get_input(){
    std::string msg;
    std::cout << "Enter message:";
    std::cin >> msg;
    return msg;
}

void error(const char *msg)
{
    perror(msg);
    exit(1);
}