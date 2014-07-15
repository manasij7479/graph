// expected output 11 101 11 1 101 01
#include "../graph.hpp"
#include "../algorithm/predicates.hpp"
#include "../algorithm/operations.hpp"
#include "../util/generate.hpp"
#include<iostream>
using namespace graph;
int main()
{
    auto g1=graph::gen::cycle(10);
    auto g4=graph::gen::cycle(3,11);
    auto g2=graph::gen::complete(10);
    auto g6=graph::gen::complete(3);
    auto g5=Union(g1,g4);
    std::cout<<isSubgraph(g1,g2);
    std::cout<<isSpanningSubgraph(g1,g2);
    
    
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
    
    std::cout<<isConnected(g1);
    
    std::cout<<isConnected(g1,"1","10")<<isConnected(g1,"1","11")<<isConnected(g1,"1","1");
    
    std::cout<<isComponent(g6,g2)<<isComponent(g4,g5);
}