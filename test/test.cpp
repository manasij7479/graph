#include "../graph.hpp"
#include "../util/io.hpp"
#include "../util/generate.hpp"
#include "../algorithm/operations.hpp"
#include <iostream>

int main()
{
    auto g1=graph::gen::generalized_petersen(5,2);
    /*auto g2=graph::gen::cycle(5,2);
    auto g=graph::Union(g1,g2);
    auto g3=graph::gen::wheel(6);*/
    graph::displayGraph(g1);
    /*std::cout<<'\n';
    graph::displayGraph(g2);
    std::cout<<'\n';
    graph::displayGraph(g);
    std::cout<<'\n';
    graph::displayGraph(g3);*/
}
