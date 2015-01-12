#ifndef GRAPH_STRUCTURE_PARENT
#define GRAPH_STRUCTURE_PARENT
#include "attribute.hpp"
#include <vector>
#include <algorithm>
namespace graph
{
    template<typename Graph>
    class ParentArray
    {
    public:
        typedef typename Graph::VertexType V;
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
        V& operator[](V v)
        {
            return parent.value(v); 
        }
    private:
        VertexAttribute<Graph,V> parent;    
    };
}
#endif