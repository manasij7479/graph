#include <iostream>
#include "../graph.hpp"

int main()
{
    graph::Graph<std::string,int> g;
    g.insertVertex("foo");
    g.insertVertex("bar");
    g.insertEdge("foo","bar",5);
    std::cout<<g.weight("foo","bar");
}
