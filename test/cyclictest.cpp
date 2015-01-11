#include "../graph.hpp"
#include "../algorithm/predicates.hpp"
#include "../util/generate.hpp"
#include<iostream>
int main()
{
    auto g1=graph::gen::cycle({10});
    auto g2=graph::gen::path({10});
    std::cout<<graph::isCyclic(g1)<<graph::isCyclic(g2);
}
