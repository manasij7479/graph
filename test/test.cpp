#include "../graph.hpp"
#include "../util/io.hpp"
#include "../util/generate.hpp"
#include <iostream>

int main()
{
    auto g=graph::gen::star(6,2);
    graph::displayGraph(g);
}
