#include "testgraph.h"
int main()
{
	auto g=getOriginalTestGraph();
	for(auto x = g.begin();x!=g.end();++x)
    {
        std::cout<<"["<<x->first<<"]->";
        for(auto y = g.nbegin(x->first);y!=g.nend(x->first);++y)
        {
            std::cout<<"("<< y->first<<","<< y->second<<")->";
        }
        std::cout<<"***\n";
    }
}