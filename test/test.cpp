#include <iostream>
#include "../graph.hpp"
#include "testgraph.h"
#include "../layout/random_layout.hpp"
int main()
{
    graph::Graph<std::string,int> g=getOriginalTestGraph();
    graph::RandomLayout<decltype(g)> layout(g);
   
        for(auto x = g.begin();x!=g.end();++x)
        {
            std::cout<<x->first<< ": ";
            graph::Point p=layout.Vertex(x->first);
            std::cout<<p.x<<' '<<p.y<<std::endl;
        }
    
}