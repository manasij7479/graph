#ifndef GRAPH_ALGORITHM_PREDICATES_HPP
#define GRAPH_ALGORITHM_PREDICATES_HPP
#include "../graph.hpp"
#include<vector>
#include<algorithm>
namespace graph
{
	template<typename Graph>
	bool isAdjacent(Graph& g,typename Graph::VertexType x,typename Graph::VertexType y )
	{
		int count=0;
		for(auto i=g.nbegin(x);i!=g.nend(x);++i)
			if(i->first==y)
				return true;
			return false;
	}
	
	template<typename Graph>
	bool isSubgraph(Graph& g,Graph& h)
	{
		if(h.order()>g.order())
			return false;
		std::vector<typename Graph::VertexType> v;
		for(auto x=g.begin();x!=g.end();++x)
			v.push_back(x->first);
		for(auto x=h.begin();x!=h.end();++x)
		{
			if(std::find(v.begin(),v.end(),x->first)==v.end())
				return false;
			else
			{
				std::vector<typename Graph::VertexType> e;
				for(auto y=g.nbegin(x->first);y!=g.nend(x->first);++y)
					e.push_back(y->first);
				for(auto y=h.nbegin(x->first);y!=h.nend(x->first);++y)
					if(std::find(e.begin(),e.end(),y->first)==e.end())
						return false;
			}
		}
		return true;
	}
	
	template<typename Graph>
	bool isSpanningSubgraph(Graph& g,Graph& h)
	{
		if(g.order()==h.order() && isSubgraph(g,h))
			return true;
		return false;
	}
}
#endif