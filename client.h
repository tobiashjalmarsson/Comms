//
// Created by tobias on 2023-10-27.
//

#include <string>
#include <utility>


#ifndef COMMS_CLIENT_H
#define COMMS_CLIENT_H


class client {
private:
    int port_number;
    std::string address;
public:
    explicit client(std::string addr = "localhost", int port = 8080){
        address = std::move(addr);
        port_number = port;
    }
    void show_info();
    void set_address(std::string addr, int port);
    int start_listen();
    int store_message(const std::string& message, int sender_port, int receiver_port) const;
};


#endif //COMMS_CLIENT_H
