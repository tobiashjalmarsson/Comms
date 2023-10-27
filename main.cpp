#include <iostream>
#include <cstdlib>
#include <string>
#include "server.h"
#include "client.h"
#include "helpers.h"

int port;
std::string address;



int main(int argc, char** argv) {
    std::string msg = get_input();
    if (argc < 4){
        std::cout << "Not enough arguments" << std::endl;
    }

    int is_server;
    is_server = std::stoi(argv[3]);
    port = std::stoi(argv[2]);
    address = argv[1];

    if (is_server){
        // Run server with inputs
        std::cout << "Running server on " << address << ":" << port << std::endl;
        start_server(address, port);
    } else {
        // Run client with inputs
        std::cout << "Running client on " << address << ":" << port << std::endl;
        start_client(address, port);
    }

    //server new_node = server();
    //new_node.show_info();
    //new_node.start_listen();

    return 0;
}
