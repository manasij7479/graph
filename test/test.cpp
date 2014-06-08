#include "../graph.hpp"

#include "../util/io.hpp"

#include <iostream>
#include <fstream>
int main()
{
    std::ifstream in("c5.txt");
    auto g=graph::makeGraph(in);
    graph::displayGraph(g);
}
