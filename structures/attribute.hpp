#ifndef GRAPH_STRUCTURE_ATTRIBUTE
#define GRAPH_STRUCTURE_ATTRIBUTE
#include <map>
/**
 * \brief attribute.hpp - Header file to store different attributes of a graph
 * **/
namespace graph
{
    template<typename Graph,typename Value>
    /**
     * \brief - class that contains graph attributes
     * **/
    class GraphAttribute
    {
    public:
        GraphAttribute(Value v_):v(v_){};
        GraphAttribute(){};
        Value& value(){return v;}
    private:
        Value v;
    };
    /**
     * \brief - class that contains Vertex attributes
     * 
     * vertex attributes contains functions to return value of a vertex, to check if a vertex
     * belongs to a graph, and the total number of vertices in a graph
     * **/
    template<typename Graph, typename Value>
    class VertexAttribute
    {
    public:
        VertexAttribute(){};
        VertexAttribute(const std::map<typename Graph::VertexType, Value>& d):data(d){}
        Value& value(typename Graph::VertexType x){return data[x];}
        bool isKnown(typename Graph::VertexType x){return data.find(x) != data.end();}
        int count(){return data.size();}
        std::map<typename Graph::VertexType, Value>& getData(){return data;}
    private:
        std::map<typename Graph::VertexType, Value> data;
    };
    /**
     * \brief - class that contains Edge attributes
     * 
     * edge attribute contains the weight of an edge when the two vertices
     * joined by the edge are given
     * **/
    template<typename Graph, typename Value>
    class EdgeAttribute
    {
        typedef typename Graph::VertexType V;///<Vertex
    public:
        EdgeAttribute(){};
        Value& value(V x, V y){return data[{x,y}];}
    private:
        std::map<std::pair<V,V>, Value> data;
    };
    
}
#endif
