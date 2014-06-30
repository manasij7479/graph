#include "../graph.hpp"
#include "../algorithm/enumeration.hpp"
#include "../util/generate.hpp"
#include<iostream>
int main()
{
    auto g=graph::gen::cycle(5);
    std::cout<<graph::degree(g,g.begin()->first);
    //std::cout<<g.begin()->first;
}