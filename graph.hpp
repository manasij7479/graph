/**
 * \brief graph.hpp - Basic Header FIle for graph implementation
 * **/
#ifndef GRAPH_GRAPH_HPP
#define GRAPH_GRAPH_HPP
#include "implementation/adjlist.hpp"
namespace graph
{
    /**
     * \brief - using Graph for AdjacencyList<VertexType,EdgeType>
     * **/
    template
    <
        typename VertexType,
        typename EdgeType
    >
    using Graph=AdjacencyList<VertexType,EdgeType>; 
}
#endif