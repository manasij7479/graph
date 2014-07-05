#include "../graph.hpp"
#include "../util/io.hpp"
#include "../util/generate.hpp"
#include <iostream>

int main()
{
    auto g=graph::gen::cycle(5);
    std::cout<<g.order();
}
