#include "../graph.hpp"
#include "../algorithm/enumeration.hpp"
#include "../algorithm/operations.hpp"
#include "../util/generate.hpp"
#include "../../../graph/util/io.hpp"
#include<iostream>
int main()
{
    auto g1=graph::gen::cycle(5);
    auto g2=graph::gen::wheel(6);
    auto g=graph::intersection(g1,g2);
    graph::displayGraph(g);
    //std::cout<<graph::degree(g,g.begin()->first);
    //std::cout<<g.begin()->first;
}