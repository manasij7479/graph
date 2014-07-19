// expected output 902 225955
#include "../graph.hpp"
#include "../algorithm/predicates.hpp"
#include "../util/generate.hpp"
#include "../algorithm/enumeration.hpp"
#include<iostream>
using namespace graph;
int main()
{
    auto g1=graph::gen::cycle(10);
    auto g3=graph::gen::complete_bipartite(3,4);
    auto g2=graph::gen::complete(10);
    auto g4=graph::gen::petersen();
    auto g5=graph::gen::path(10);
    auto g6=graph::gen::desargues();
    
    std::cout<<nregular(g2);
    std::cout<<nregular(g3);
    std::cout<<nregular(g1);
    
    std::cout<<Radius(g4)<<Diameter(g4);
    std::cout<<Radius(g5)<<Diameter(g5);
    std::cout<<Radius(g6)<<Diameter(g6);
}