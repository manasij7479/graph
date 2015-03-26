#ifndef GRAPH_STRUCTURE_PARENT
#define GRAPH_STRUCTURE_PARENT
#include "attribute.hpp"
#include <vector>
#include <algorithm>
/**
 * \brief - parent.hpp - header file containing structure to hold paths of vertices of a graph
 * **/
namespace graph
{
    template<typename Graph>
    class ParentArray
    {
    public:
        typedef typename Graph::VertexType V;///<Vertex
        /**
         * \brief - returns the path of a particular vertex of a graph
         * 
         * @param V v- Parameter, a vertex
         * 
         * @returns std::vector<V> result - the path of vertex v
         * **/
        std::vector<V> getPath(V v)
        {
            std::vector<V> result;
            while(true)
            {
                result.push_back(v);
                auto p = parent.value(v);
                if (p == v)
                    break;
                v = p;
            }
            std::reverse(result.begin(), result.end());
            return result;
        }
        
        bool isKnown(typename Graph::VertexType x){return parent.isKnown(x);}
        
        V& operator[](V v)
        {
            return parent.value(v); 
        }
    private:
        VertexAttribute<Graph,V> parent;    
    };
}
#endif
