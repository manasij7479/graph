#ifndef GRAPH_ALGORITHM_PREDICATES_HPP
#define GRAPH_ALGORITHM_PREDICATES_HPP
#include "../graph.hpp"
namespace graph
{
	template
	<
	typename VertexType,
	typename EdgeType
	>
	
	bool isAdjacent(Graph<VertexType,EdgeType>& g, VertexType x, VertexType y )
	{
		int count=0;
		for(auto i=g.nbegin(x);i!=g.nend(x);++i)
			if(i->first==y)
				return true;
			return false;
	}
}
#endif