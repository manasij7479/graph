#ifndef GRAPH_STRUCTURE_ATTRIBUTE
#define GRAPH_STRUCTURE_ATTRIBUTE
#include <map>
namespace graph
{
    template<typename Graph,typename Value>
    class GraphAttribute
    {
    public:
        GraphAttribute(Value v_):v(v_){};
        GraphAttribute(){};
        Value& value(){return v;}
    private:
        Value v;
    };
    
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
    
    template<typename Graph, typename Value>
    class EdgeAttribute
    {
        typedef typename Graph::VertexType V;
    public:
        EdgeAttribute(){};
        Value& value(V x, V y){return data[{x,y}];}
    private:
        std::map<std::pair<V,V>, Value> data;
    };
    
}
#endif