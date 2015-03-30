#include "../graph.hpp"
#include "../util/generate.hpp"
#include "../util/io.hpp"
#include "../algorithm/mst.hpp"
#include <iostream>
using namespace graph;
int main()
{
   auto g = graph::gen::cycle({10});
   auto s = graph::Prim(g);
   auto p = s.getSpan();
   auto x = s.getMst();
   std::cout<<p<<std::endl;
   displayGraph(x);
   
   std::cout<<std::endl<<std::endl<<std::endl<<std::endl;
   Graph <int, int> g5(true);
    g5.insertVertex(1);
    g5.insertVertex(2);
    g5.insertVertex(3);
    g5.insertVertex(4);
    g5.insertEdge(1,2,7);
    g5.insertEdge(2,3,3);
    g5.insertEdge(3,4,6);
    g5.insertEdge(4,1,2);
    g5.insertEdge(1,3,1);
    g5.insertEdge(2,4,1);
   auto s1 = graph::Boruvka(g5);
   auto p1 = s1.getSpan();
   auto x1 = s1.getMst();
   std::cout<<p1<<std::endl;
   displayGraph(x1);
}
