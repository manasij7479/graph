#include "../graph.hpp"
#include "../util/generate.hpp"
#include "../algorithm/apsp.hpp"
#include <iostream>
using namespace graph;
int main()
{
   auto g = graph::gen::cycle({10});
   auto s = graph::FloydRoyWarshall(g);
   auto p = s.getPathArray();
   for(auto i=p.begin();i!=p.end();++i)
   {
     std::cout<<"[ "<<i->first.first<<" , "<<i->first.second<<" ] ==>> ";
     for(auto j=i->second.begin();j!=i->second.end();++j)
         std::cout<<*j<<" ";
     std::cout<<std::endl;
   }
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
   auto s1 = graph::FloydRoyWarshall(g5);
   auto p1 = s1.getPathArray();
   for(auto i=p1.begin();i!=p1.end();++i)
   {
     std::cout<<"[ "<<i->first.first<<" , "<<i->first.second<<" ] ==>> ";
     for(auto j=i->second.begin();j!=i->second.end();++j)
         std::cout<<*j<<" ";
     std::cout<<std::endl;
   }
}
