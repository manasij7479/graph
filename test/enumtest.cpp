// expected output 902 225955 10.5
#include "../graph.hpp"
#include "../algorithm/predicates.hpp"
#include "../util/generate.hpp"
#include "../algorithm/enumeration.hpp"
#include<iostream>
using namespace graph;
int main()
{
    Graph <std::string, int> g;
    g.insertVertex("1");
    g.insertVertex("2");
    g.insertVertex("3");
    g.insertVertex("4");
    g.insertEdge("1","2",1);
    g.insertEdge("2","3",1);
    g.insertEdge("4","2",1);
    auto g1=graph::gen::cycle(10);
    auto g3=graph::gen::complete_bipartite(3,4);
    auto g2=graph::gen::complete(10);
    auto g4=graph::gen::petersen();
    auto g5=graph::gen::path(10);
    auto g6=graph::gen::desargues();
    
    std::cout<<nregular(g2);
    std::cout<<nregular(g3);
    std::cout<<nregular(g1);
    
    std::cout<<Radius(g4)<<Diameter(g4);
    std::cout<<Radius(g5)<<Diameter(g5);
    std::cout<<Radius(g6)<<Diameter(g6);
    
    std::cout<<Density(g2)<<Density(g);
}