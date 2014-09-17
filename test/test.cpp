#include "../graph.hpp"
#include "../algorithm/sssp.hpp"
#include "../algorithm/predicates.hpp"
#include "../algorithm/enumeration.hpp"
#include "../algorithm/operations.hpp"
#include "../algorithm/collections.hpp"
#include "../util/generate.hpp"
#include "../util/visitors.hpp"
#include "../structures/attribute.hpp"
#include <iostream>
#include <functional>
int main()
{
    auto g1=graph::gen::cycle(5);
    auto d=graph::BellmanFord(g1,"1");
    graph::VertexAttribute<decltype(g1),int> dist;
    
    for (auto v : VertexList(g1))
        dist.value(v) = d[v].first;
    for (auto v : VertexList(g1))
        std::cout<<dist.value(v); 
}
