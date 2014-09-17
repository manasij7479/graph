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
            V temp=v;
            while(parent.value(v)!=temp)
            {
                result.push_back(temp);
                temp=parent.value(temp);
            }
            result.push_back(temp);
            std::reverse(result.begin(),result.end());
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