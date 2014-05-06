#ifndef GRAPH_GRAPH_HPP
#define GRAPH_GRAPH_HPP

namespace graph
{
    //EdgePolicy Requirements
    template
    <
        typename VertexType,
        typename EdgeType,
        typename EdgePolicy
    >
    class AdjacencyList:public EdgePolicy
    {
        
    };
    
    
    template
    <
        typename VertexType,
        typename EdgeType,
        typename EdgePolicy
    >
    using Graph=AdjacencyList<VertexType,EdgeType,EdgePolicy>;
    
}
#endif