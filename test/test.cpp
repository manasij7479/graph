#include "../graph.hpp"
#include "../algorithm/predicates.hpp"
#include "../algorithm/operations.hpp"
#include "../util/generate.hpp"
#include<iostream>
int main()
{
    auto g1=graph::gen::path(10);
    std::cout<<graph::isPeriphery(g1,"5");
    
    
}
