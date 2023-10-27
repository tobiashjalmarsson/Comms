//
// Created by tobias on 2023-10-27.
//

#include "client.h"


#include <iostream>
#include <string>
#include <utility>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <error.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

void client::show_info() {
    std::cout << "Address: " << address << ":" << port_number << std::endl;
}

void client::set_address(std::string addr, int port) {
    std::cout << "Setting server info.." << std::endl;
    port_number = port;
    address = std::move(addr);
    show_info();
}

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

/*
 * Start listening to preset
 * address:port
 * */
void client::start_listen(){
    std::cout << "Client listening" << std::endl;
    int status, valread, client_fd;
    struct sockaddr_in serv_addr;
    char* hello = "Hello from client";
    char buffer[1024] = { 0 };
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port_number);

    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
        <= 0) {
        printf(
                "\nInvalid address/ Address not supported \n");
    }

    if ((status
                 = connect(client_fd, (struct sockaddr*)&serv_addr,
                           sizeof(serv_addr)))
        < 0) {
        printf("\nConnection Failed \n");
    }
    send(client_fd, hello, strlen(hello), 0);
    printf("Hello message sent\n");
    valread = read(client_fd, buffer, 1024 - 1); // subtract 1 for the null terminator at the end
    printf("%s\n", buffer);

    // closing the connected socket
    close(client_fd);
}
