#include "../graph.hpp"
#include "../algorithm/predicates.hpp"
//#include "../algorithm/enumeration.hpp"
#include<iostream>
int main()
{
    graph::Graph<std::string,int> g(false);
    g.insertVertex("foo");
    g.insertVertex("bar");
    g.insertEdge("foo","bar",4);
//     g.removeEdge("foo","bar");
//    g.removeVertex("bar");
    
    for(auto x = g.begin();x!=g.end();++x)
    {
        std::cout<<"["<<x->first<<"]->";
        for(auto y = g.nbegin(x->first);y!=g.nend(x->first);++y)
        {
            std::cout<<"("<< y->first<<","<< y->second<<")->";
        }
        std::cout<<"***\n";
    }
    
    std::cout<<graph::isAdjacent<std::string,int>(g,"foo","bar");
}