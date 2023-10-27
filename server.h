//
// Created by tobias on 2023-10-27.
//
#include <string>
#include <utility>

#ifndef COMMS_NODE_H
#define COMMS_NODE_H


class node {
private:
    int port_number;
    std::string port_address;
public:
    explicit node(std::string addr = "localhost", int port = 8080){
        port_address = std::move(addr);
        port_number = port;
    }
    void show_info();
    void set_address(std::string addr, int port);
    void start_listen();
};


#endif //COMMS_NODE_H
