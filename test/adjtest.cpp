// expected output 0 0 1
#include "../graph.hpp"
#include "../algorithm/predicates.hpp"
#include "../util/generate.hpp"
#include<iostream>
using namespace graph;
int main()
{
    auto g1=graph::gen::cycle({10});
    if(isAdjacent(g1,1,6))
        std::cout<<"1";
    else
        std::cout<<"0";
   
    auto g2=graph::gen::cycle({10});
    if(isAdjacent(g2,1,11))
        std::cout<<"1";
    else
        std::cout<<"0";
   
    auto g3=graph::gen::complete({10});
    if(isAdjacent(g3,4,3))
        std::cout<<"1";
    else
        std::cout<<"0";
}
