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
#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void client::show_info() {
    std::cout << "Address: " << address << ":" << port_number << std::endl;
}

void client::set_address(std::string addr, int port) {
    std::cout << "Setting server info.." << std::endl;
    port_number = port;
    address = std::move(addr);
    show_info();
}

/*
 * Start listening to preset
 * address:port
 * */
int client::start_listen(){
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    bool new_message = true;
    char buffer[256];

    portno = port_number;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    server = gethostbyname("localhost");
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
            server->h_length);
    serv_addr.sin_port = htons(port_number);
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    error("ERROR connecting");

    while (new_message)
    {
        printf("Please enter the message: ");
        bzero(buffer,256);
        fgets(buffer,255,stdin);

        std::cout << "Buffer is: " << buffer << std::endl;

        //bool is_disconnect = std::string(buffer).find("disconnect") != std::string::npos;
        std::cout << "new_message: " << new_message << std::endl;
        new_message = std::string(buffer).find("disconnect") == std::string::npos;


        n = write(sockfd, buffer, strlen(buffer));
        if (n < 0)
            error("ERROR writing to socket");
        bzero(buffer,256);
        n = read(sockfd, buffer, 255);
        if (n < 0)
            error("ERROR reading from socket");
        printf("%s\n", buffer);
    }

    close(sockfd);
    return 0;
}
