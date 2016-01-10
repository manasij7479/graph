#ifndef GRAPH_UTIL_GMLPARSESTATE_HPP
#define GRAPH_UTIL_GMLPARSESTATE_HPP
#include<vector>
#include<tuple>
#include "../../graph.hpp"
namespace graph
{
    template<typename Graph>
    class GMLParseState
    {
    public:
        
        void addDirectedStatus(bool status) { directedStatus = status; }
        void addVertex(typename Graph::VertexType v) { vertices.push_back(v); }
        void addEdge(typename Graph::VertexType src, typename Graph::VertexType dest, typename Graph::EdgeType w)
        {
            edges.push_back(std::make_tuple(src, dest, w));
        }
        
        bool getDirectedStatus() { return directedStatus; }
        std::vector<typename Graph::VertexType> getVertices() { return vertices; }
        std::vector
        <
            std::tuple
            <
                typename Graph::VertexType, 
                typename Graph::VertexType, 
                typename Graph::EdgeType
            >
       >
       getEdges() 
       { 
           return edges;
       }
       
       void clear()
       {
            vertices.clear();
            edges.clear();
       }
    private:
        bool directedStatus;
        std::vector<typename Graph::VertexType> vertices;
        std::vector
        <
            std::tuple
            <
                typename Graph::VertexType, 
                typename Graph::VertexType, 
                typename Graph::EdgeType
            >
       > edges;
    };
}
#endif