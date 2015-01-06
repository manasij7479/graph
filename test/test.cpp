#include "../graph.hpp"
#include "../algorithm/sssp.hpp"
#include "../algorithm/predicates.hpp"
#include "../algorithm/enumeration.hpp"
#include "../algorithm/operations.hpp"
#include "../algorithm/collections.hpp"
#include "../util/generate.hpp"
#include "../util/visitors.hpp"
#include "../structures/attribute.hpp"
#include "../algorithm/coloring.hpp"
#include <iostream>
#include <functional>
int main()
{
    auto g1=graph::gen::complete({4});
    auto g2=graph::gen::path({2});
    //auto d=graph::BellmanFord(g1,"1");
    graph::Coloring<decltype(g1)> cObj(g1);
    int i=cObj.getChromaticNo();
    std::cout<<i;
}
