#include "testgraph.h"
int main()
{
	
	auto g=getOriginalTestGraph();
	g.removeVertex("a");
	g.removeEdge("d","h");
	g.removeVertex("b");
	g.removeVertex("g");
	g.removeVertex("h");
	g.removeEdge("d","f");
	g.removeVertex("c");
	g.removeVertex("d");
	g.removeVertex("e");
	g.removeVertex("f");
	auto result=0;
	for(auto x = g.begin();x!=g.end();++x)
		result++;
	
    std::cout<<result;
}