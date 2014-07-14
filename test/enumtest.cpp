// expected output 902
#include "../graph.hpp"
#include "../algorithm/predicates.hpp"
#include "../util/generate.hpp"
#include<iostream>
using namespace graph;
int main()
{
    auto g1=graph::gen::cycle(10);
    auto g3=graph::gen::complete_bipartite(3,4);
    auto g2=graph::gen::complete(10);
    
    std::cout<<nregular(g2);
    std::cout<<nregular(g3);
    std::cout<<nregular(g1);
}