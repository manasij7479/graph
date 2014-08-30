// expected output 11 101 11 1 101 01 1100 1100 10 10
#include "../graph.hpp"
#include "../algorithm/predicates.hpp"
#include "../algorithm/operations.hpp"
#include "../util/generate.hpp"
#include<iostream>
using namespace graph;
int main()
{
    auto g1=graph::gen::cycle(10);
    auto g2=graph::gen::complete(10);
    auto g4=graph::gen::cycle(3,11);
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
    
    std::cout<<isCentre(g3,"5")<<isCentre(g3,"6")<<isCentre(g3,"4")<<isCentre(g3,"11");
    
    std::cout<<isPeriphery(g3,"1")<<isPeriphery(g3,"10")<<isPeriphery(g3,"4")<<isPeriphery(g3,"11");
    
    auto h1=graph::gen::star_polygon(5,2);
    std::cout<<graph::isSparse(h1);
    auto h2=graph::gen::complete_bipartite(5,2);
    std::cout<<graph::isSparse(h2);
    
    graph::Graph <std::string, int> h;
    h.insertVertex("1");
    h.insertVertex("2");
    h.insertVertex("3");
    h.insertVertex("4");
    h.insertEdge("1","2",1);
    h.insertEdge("2","3",1);
    h.insertEdge("4","2",1);
    std::cout<<graph::isTree(h);
    h.insertEdge("4","1",1);
    std::cout<<graph::isTree(h);
}
