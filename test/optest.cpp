// expected output 1 1 1 1 1 0 9
#include "../graph.hpp"
#include "../algorithm/predicates.hpp"
#include "../util/generate.hpp"
#include<iostream>
using namespace graph;
int main()
{
     auto g1=graph::gen::cycle(10);
     auto g2=complement(g1);
     auto g3=Union(g1,g2);
     std::cout<<isComplete(g3);
     std::cout<<isComplement(g1,g2);
     
    Graph <std::string, int> g5(false);
    g5.insertVertex("1");
    g5.insertVertex("2");
    g5.insertVertex("3");
    auto g4=graph::gen::path(3);
    auto h=intersection(g4,g5);
    std::cout<<isEdgeless(h);
    
    Graph <std::string, int> g6(false);
    g6.insertVertex("1");
    auto g7=graph::gen::complete(10);
    auto g8=join(g6,g7);
    std::cout<<isComplete(g8);
        
    auto g9=graph::gen::complete(10);
    auto g10=symmetric_difference(g9,g9);
    std::cout<<isEmpty(g10);
    
    auto g12=graph::gen::path(10);
    g12=graph::EdgeDeletionSubgraph(g12,"1","2");
    std::cout<<graph::isConnected(g12);
    
    auto g11=graph::gen::path(10);
    g11=graph::VertexDeletionSubgraph(g11,"1");
    std::cout<<g11.order();
    
}
