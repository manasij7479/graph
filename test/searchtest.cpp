#include "../graph.hpp"
#include "../algorithm/predicates.hpp"
#include "../algorithm/search.hpp"
#include "../util/generate.hpp"
#include<iostream>
using namespace graph;
int main()
{
	std::cout<<"\nnormal undirected graph\n";
	Graph<std::string,int> g;
    g.insertVertex("1");
    g.insertVertex("2");
    g.insertVertex("3");
    g.insertVertex("4");
    g.insertVertex("5");
    g.insertVertex("6");
    g.insertVertex("7");
    g.insertEdge("1","2",1);
    g.insertEdge("1","3",3);
    g.insertEdge("1","4",2);
    g.insertEdge("2","5",5);
    g.insertEdge("2","6",3);
    g.insertEdge("3","7",4);
    auto f = [](std::string v)
    {
        std::cout<<v;
        return true;
    }; 
    DepthFirstSearch<decltype(g)> bfs(g,g.begin()->first);
    BreadthFirstSearch<decltype(g)> dfs(g,g.begin()->first);
    UniformCostSearch<decltype(g)> ucs(g,g.begin()->first);
    bfs.setp2(f);
    dfs.setp2(f);
    ucs.setp2(f);
    bfs();
    std::cout<<"\n";
    dfs();
	std::cout<<"\n";
    ucs();
	std::cout<<"\n\n";
	auto d1=bfs.getParentArray();
    for(auto i=d1.begin();i!=d1.end();i++)
		std::cout<<i->first<<" "<<i->second<<"\n";
    std::cout<<"\n";
    auto x1=bfs.getDistanceArray();
    for(auto i=x1.begin();i!=x1.end();i++)
		std::cout<<i->first<<" "<<i->second<<"\n";
    std::cout<<"\n";
    auto d2=dfs.getParentArray();
    for(auto i=d2.begin();i!=d2.end();i++)
		std::cout<<i->first<<" "<<i->second<<"\n";
	std::cout<<"\n";
    auto x2=dfs.getDistanceArray();
    for(auto i=x2.begin();i!=x2.end();i++)
		std::cout<<i->first<<" "<<i->second<<"\n";
	std::cout<<"\n";	
    auto d3=ucs.getParentArray();
    for(auto i=d3.begin();i!=d3.end();i++)
		std::cout<<i->first<<" "<<i->second<<"\n";
	std::cout<<"\n";
    auto x3=ucs.getDistanceArray();
    for(auto i=x3.begin();i!=x3.end();i++)
		std::cout<<i->first<<" "<<i->second<<"\n";
	std::cout<<"\n";	
	
	
	std::cout<<"\npath graph\n";
	
	Graph<std::string,int> g2;
    g2.insertVertex("1");
    g2.insertVertex("2");
    g2.insertVertex("3");
    g2.insertVertex("4");
    g2.insertVertex("5");
    g2.insertVertex("6");
    g2.insertVertex("7");
    g2.insertEdge("1","2",1);
    g2.insertEdge("2","3",3);
    g2.insertEdge("3","4",2);
    g2.insertEdge("4","5",5);
    g2.insertEdge("5","6",3);
    g2.insertEdge("6","7",4);
    DepthFirstSearch<decltype(g2)> bfs2(g2,g2.begin()->first);
    BreadthFirstSearch<decltype(g2)> dfs2(g2,g2.begin()->first);
    UniformCostSearch<decltype(g2)> ucs2(g2,g2.begin()->first);
    bfs2.setp2(f);
    dfs2.setp2(f);
    ucs2.setp2(f);
    bfs2();
    std::cout<<"\n";
    dfs2();
	std::cout<<"\n";
    ucs2();
	std::cout<<"\n\n";
	
	std::cout<<"\ndirected graph\n";
	
	Graph<std::string,int> g3(true);
    g3.insertVertex("1");
    g3.insertVertex("2");
    g3.insertVertex("3");
    g3.insertVertex("4");
    g3.insertVertex("5");
    g3.insertVertex("6");
    g3.insertVertex("7");
    g3.insertEdge("1","2",2);
    g3.insertEdge("1","3",3);
    g3.insertEdge("2","4",1);
    g3.insertEdge("3","2",2);
    g3.insertEdge("5","4",5);
    g3.insertEdge("6","5",3);
    g3.insertEdge("3","7",4);
    g3.insertEdge("7","6",1);
    DepthFirstSearch<decltype(g3)> bfs3(g3,g3.begin()->first);
    BreadthFirstSearch<decltype(g3)> dfs3(g3,g3.begin()->first);
    UniformCostSearch<decltype(g3)> ucs3(g3,g3.begin()->first);
    bfs3.setp2(f);
    dfs3.setp2(f);
    ucs3.setp2(f);
    bfs3();
    std::cout<<"\n";
    dfs3();
	std::cout<<"\n";
    ucs3();
	std::cout<<"\n\n";
	
	auto d4=bfs3.getParentArray();
    for(auto i=d4.begin();i!=d4.end();i++)
		std::cout<<i->first<<" "<<i->second<<"\n";
    std::cout<<"\n";
    auto x4=bfs3.getDistanceArray();
    for(auto i=x4.begin();i!=x4.end();i++)
		std::cout<<i->first<<" "<<i->second<<"\n";
    std::cout<<"\n";
    
}
