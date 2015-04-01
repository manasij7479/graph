// expeted output 999
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
   auto s1 = graph::Boruvka(g);
   auto p1 = s1.getSpan();
   auto x1 = s1.getMst();
   auto s2 = graph::Kruskal(g, [](int, int, int){});
   auto p2 = s2.getSpan();
   auto x2 = s2.getMst();
   std::cout<<p<<p1<<p2;
}
