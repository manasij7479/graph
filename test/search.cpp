#include "../graph.hpp"

#include "../search/search.hpp"
#include "../search/ucs.hpp"

int main()
{
    graph::Graph<std::string,int> g(true);
    g.insertVertex("a");
    g.insertVertex("b");
    g.insertVertex("c");
    g.insertVertex("d");
    g.insertVertex("e");
    g.insertVertex("f");
    g.insertVertex("g");
    g.insertVertex("h");
    
    g.insertEdge("a","b",1);
    g.insertEdge("a","c",1);
    g.insertEdge("a","d",4);
    g.insertEdge("b","c",2);
    g.insertEdge("b","e",3);
    g.insertEdge("c","g",1);
    g.insertEdge("d","h",200);
    g.insertEdge("d","f",1);
    g.insertEdge("f","g",3);
    g.insertEdge("e","h",5);
    g.insertEdge("h","g",4);
    
    for(auto x = g.begin();x!=g.end();++x)
    {
        std::cout<<"["<<x->first<<"]->";
        for(auto y = g.nbegin(x->first);y!=g.nend(x->first);++y)
        {
            std::cout<<"("<< y->first<<","<< y->second<<")->";
        }
        std::cout<<"***\n";
    }
    
    graph::UniformCostSearch<decltype(g)> ucs(g,"a");
    std::cout<<ucs.distanceTo("h");
    
    
    
}