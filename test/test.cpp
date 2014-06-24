#include "../graph.hpp"
#include "../util/io.hpp"
#include "../util/generate.hpp"
#include <iostream>

int main()
{
    auto g=graph::gen::wagner();
    graph::displayGraph(g);
}
