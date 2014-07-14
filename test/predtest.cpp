// expected output 11 101 11
#include "../graph.hpp"
#include "../algorithm/predicates.hpp"
#include "../util/generate.hpp"
#include<iostream>
using namespace graph;
int main()
{
    auto g1=graph::gen::cycle(10);
    auto g2=graph::gen::complete(10);
    std::cout<<isSubgraph(g2,g1);
    std::cout<<isSpanningSubgraph(g2,g1);
    
    
    Graph <std::string, int> g(true);
    g.insertVertex("1");
    g.insertVertex("2");
    g.insertVertex("3");
    g.insertEdge("1","2",1);
    g.insertEdge("2","3",1);
    g.insertEdge("3","1",1);
    auto g3=graph::gen::path(10);
    std::cout<<isRegular(g1);
    std::cout<<isRegular(g3);
    std::cout<<isRegular(g);
    
    
    std::cout<<isEulerian(g1);
    std::cout<<isSemiEulerian(g3);
}