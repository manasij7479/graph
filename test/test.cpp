#include "../graph.hpp"
#include "../util/generate.hpp"
#include "../layout/random_layout.hpp"
int main()
{
    auto g=graph::gen::cycle(5);
    graph::RandomLayout<decltype(g)> layout(g);
   
        for(auto x = g.begin();x!=g.end();++x)
        {
            std::cout<<x->first<< ": ";
            graph::Point p=layout.Vertex(x->first);
            std::cout<<p.x<<' '<<p.y<<std::endl;
        }
}