#include "../graph.hpp"
#include "../util/io.hpp"
#include "../util/generate.hpp"
#include <iostream>

int main()
{
    auto g=graph::gen::complete_bipartite(2,6,110);
    graph::displayGraph(g);
}
