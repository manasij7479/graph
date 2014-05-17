#include "../graph.hpp"

#include "../search/search.hpp"
#include "../search/ucs.hpp"
#include "../search/dfs.hpp"
#include "../search/bfs.hpp"
#include<vector>
#include<string>
#include<iostream>

int main()
{
    graph::Graph<std::string,int> g(false);
    g.insertVertex("1");
    g.insertVertex("2");
    g.insertVertex("3");
    g.insertVertex("4");
    g.insertVertex("5");
    g.insertVertex("6");
    //g.insertVertex("g");
    //g.insertVertex("h");
    
    g.insertEdge("1","2",1);
    g.insertEdge("1","3",1);
    g.insertEdge("2","3",4);
    g.insertEdge("2","4",2);
    g.insertEdge("2","5",3);
    g.insertEdge("3","5",1);
    g.insertEdge("4","5",2);
    g.insertEdge("5","6",1);
    //g.insertEdge("f","g",3);
    //g.insertEdge("e","h",5);
    //g.insertEdge("h","g",4);
    
    for(auto x = g.begin();x!=g.end();++x)
    {
        std::cout<<"["<<x->first<<"]->";
        for(auto y = g.nbegin(x->first);y!=g.nend(x->first);++y)
        {
            std::cout<<"("<< y->first<<","<< y->second<<")->";
        }
        std::cout<<"***\n";
    }
    
    graph::DepthFirstSearch<decltype(g)> dfs(g,"1");
    std::vector<std::string> v;
    for(auto x=g.begin();x!=g.end();++x)
	{
		v=dfs.getPath(x->first);
		for(int i=0;i<v.size();++i)
			std::cout<<v[i];
		std::cout<<'\n';
	}
    
    
}