#ifndef GRAPH_SEARCH_DFS_HPP
#define GRAPH_SEARCH_DFS_HPP
#include "search.hpp"
namespace graph
{
    template<typename GraphType>
    class Stack
    {
    public:
        typedef typename GraphType::EdgeType E;
        typedef typename GraphType::VertexType V;
        
        Stack(std::map<V,typename edge_traits<E>::DistanceType>&){}
        void put(V t)
        {
            data.push_back(t);
        }
        V get()
        {
            V result=data.back();
            data.pop_back();
            return result;
        }
        bool empty()
        {
            return data.empty();
        }
    private:
        std::vector<V> data;
    };
    
    template<typename G>
    using DepthFirstSearch=Search<G,Stack>;
    
}
#endif