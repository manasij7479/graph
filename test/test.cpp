#include "../graph.hpp"
#include "../algorithm/predicates.hpp"
#include "../algorithm/operations.hpp"
#include "../algorithm/collections.hpp"
#include "../util/generate.hpp"
#include<iostream>
int main()
{
    /*auto g1=graph::gen::path(10);
    std::cout<<graph::isPeriphery(g1,"5");*/
    graph::Graph <std::string, int> g(true);
    g.insertVertex("1");
    g.insertVertex("2");
    g.insertVertex("3");
    g.insertVertex("4");
    g.insertEdge("1","2",1);
    g.insertEdge("2","3",1);
    g.insertEdge("3","1",1);
    g.insertEdge("4","2",1);
    
    auto v1=graph::outVertexList(g,"2");
    auto v2=graph::inVertexList(g,"2");
    
    for(auto i:v1)
        std::cout<<i<<std::endl;
    for(auto i:v2)
        std::cout<<i<<std::endl;    
    
}
