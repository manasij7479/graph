#ifndef GRAPH_GRAPH_HPP
#define GRAPH_GRAPH_HPP
#include "implementation/adjlist.hpp"
namespace graph
{
    template
    <
        typename VertexType,
        typename EdgeType
    >
    using Graph=AdjacencyList<VertexType,EdgeType>; 
}
#endif