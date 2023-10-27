#ifndef __node_H_INCLUDED__ // if Node.h hasn't been included yet...
#define __node_H_INCLUDED__ //   #define this so the compiler knows it has been included

#include <string>
#include <iostream>
class node
{
private:
    int portnumber; // Port of the node
    int node_fd;    // File descriptor
    int opt = 1;
    std::string address; // Address of the node, e.g address:port

public:
    void set_info(std::string addr, int port);
    void print_info(void);
    void listen(void);
};
#endif
