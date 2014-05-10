#ifndef GRAPH_ALGORITHM_ENUMERATION_HPP
#define GRAPH_ALGORITHM_ENUMERATION_HPP    
#include "../graph.hpp"
namespace graph
{
	template
	<
	typename VertexType,
	typename EdgeType
	>
	
	int outdegree(Graph<VertexType,EdgeType>& g, VertexType v)
	{
		int count=0;
		for(auto i=g.nbegin(v);i!=g.nend(v);++i)
			count++;
		return count;
	}
	
	template
	<
	typename VertexType,
	typename EdgeType
	>
	
	int indegree(Graph<VertexType,EdgeType>& g, VertexType v)
	{
		int count=0;
		if(!g.directed)
			return outdegree(v);
		else
		{
			for(auto x=g.begin();x!=g.end();++x)
			{
				for(auto y=g.nbegin(x);y!=g.nend(x);++y)
					if(y->first==v)
						count++;
			}
			return count;
		}
	}
	
	template
	<
	typename VertexType,
	typename EdgeType
	>
	
	int degree(Graph<VertexType,EdgeType>& g, Vertextype v)
	{
		if(!g.directed)
			return outdegree(v);
		else
			return indegree(v)+outdegree(v);
	}
}
#endif