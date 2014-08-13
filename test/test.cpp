#include "../graph.hpp"
#include "../algorithm/sssp.hpp"
#include "../algorithm/predicates.hpp"
#include "../algorithm/enumeration.hpp"
#include "../algorithm/operations.hpp"
#include "../algorithm/collections.hpp"
#include "../util/generate.hpp"
#include<iostream>
int main()
{
    auto g1=graph::gen::cycle(5);
    auto d=graph::BellmanFord(g1,"1");
    for (auto v : VertexList(g1))
        std::cout<<v<<' '<<d[v].first <<' '<< d[v].second<<std::endl;
}
