#include "../graph.hpp"
#include "../algorithm/sssp.hpp"
#include "../algorithm/predicates.hpp"
#include "../algorithm/operations.hpp"
#include "../algorithm/collections.hpp"
#include "../util/generate.hpp"
#include<iostream>
int main()
{
    /*auto g1=graph::gen::cycle(5);
    auto v1=graph::Djikstra(g1,"1");*/
    /*auto g2=graph::gen::complete_bipartite(5,2);
    std::cout<<graph::isSparse(g2);*/
    /*std::cout<<graph::isPeriphery(g1,"5");*/
    graph::Graph <std::string, int> g;
    g.insertVertex("1");
    g.insertVertex("2");
    g.insertVertex("3");
    g.insertVertex("4");
    g.insertEdge("1","2",1);
    g.insertEdge("2","3",1);
    g.insertEdge("4","2",1);
    std::cout<<graph::isTree(g);
    
    /*
    auto v1=graph::outVertexList(g,"2");
    auto v2=graph::inVertexList(g,"2");
    */
    /*for(auto i:v1)
        std::cout<<i.first<<" "<<i.second<<std::endl;
    /*for(auto i:v2)
        std::cout<<i<<std::endl;    */
}
