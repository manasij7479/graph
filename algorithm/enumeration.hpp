#ifndef GRAPH_ALGORITHM_ENUMERATION_HPP
#define GRAPH_ALGORITHM_ENUMERATION_HPP    
#include "../graph.hpp"
namespace graph
{
	template<typename Graph>
	int outDegree(Graph& g, typename Graph::VertexType v)
	{
		int count=0;
		for(auto i=g.nbegin(v);i!=g.nend(v);++i)
			count++;
		return count;
	}
	
    template<typename Graph>
	int inDegree(Graph& g, typename Graph::VertexType v)
	{
		int count=0;
		if(!g.isDirected())
			return outDegree(g,v);
		else
		{
			for(auto x=g.begin();x!=g.end();++x)
			{
				for(auto y=g.nbegin(x->first);y!=g.nend(x->first);++y)
					if(y->first==v)
						count++;
			}
			return count;
		}
	}
	
	template<typename Graph>
	int degree(Graph& g,typename Graph::Vertextype v)
	{
		if(!g.isDirected())
			return outDegree(g,v);
		else
			return inDegree(g,v)+outDegree(g,v);
	}
}
#endif