#include "../graph.hpp"
#include "../util/io.hpp"
#include "../util/generate.hpp"
#include <iostream>

int main()
{
    auto g=graph::gen::mobius_ladder(5,3);
    graph::displayGraph(g);
}
