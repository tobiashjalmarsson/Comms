#include <iostream>
#include "node.h"

//  g++ -std=c++11 node.cpp main.cpp node.h -o another

int main()
{
    std::cout << "Running process.." << std::endl;
    node first_node;
    first_node.set_info("localhost", 8080);
    first_node.print_info();
    return 0;
}