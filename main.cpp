#include <iostream>
#include <cstdlib>
#include <string>
#include "server.h"
#include "client.h"

int port;
std::string address;

void start_server(){
    std::cout << "Starting server##" << std::endl;
    server s = server(address, port);
    s.start_listen();
}

void start_client(){
    std::cout << "Starting client##" << std::endl;
    client c = client(address, port);
    c.start_listen();

}

int main(int argc, char** argv) {
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
        start_server();
    } else {
        // Run client with inputs
        std::cout << "Running client on " << address << ":" << port << std::endl;
        start_client();
    }

    //server new_node = server();
    //new_node.show_info();
    //new_node.start_listen();

    return 0;
}
