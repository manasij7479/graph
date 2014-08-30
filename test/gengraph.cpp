// expected output 0 1
#include "../graph.hpp"
#include "../algorithm/predicates.hpp"
#include "../util/generate.hpp"
#include<iostream>
using namespace graph;
int main()
{
    Graph <std::string, int> g(true);
    g.insertVertex("1");
    g.insertVertex("2");
    g.insertVertex("3");
    g.insertEdge("1","2",1);
    g.insertEdge("2","3",1);
    g.insertEdge("3","1",1);
    
     std::cout<<isAdjacent(g,"1","3")<<isAdjacent(g,"3","1");
        
}