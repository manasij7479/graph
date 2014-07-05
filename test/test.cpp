#include "../graph.hpp"
#include "../algorithm/predicates.hpp"
#include "../util/generate.hpp"
#include<iostream>
int main()
{
    auto g=graph::gen::path(100);
    std::cout<<graph::isCyclic(g);
}