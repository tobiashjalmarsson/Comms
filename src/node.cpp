#include <iostream>
#include <string>
#include "node.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

void node::set_info(std::string addr, int port)
{
    portnumber = port;
    address = addr;
}

void node::print_info(void)
{
    std::cout << "Address: " << address << ":" << portnumber << std::endl;
}

void node::listen(void)
{
    // Create socket fd
    if ((node_fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
    {
        perror("Failed to init node");
    }

    // Attach socket
    if (setsockopt(node_fd, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
}