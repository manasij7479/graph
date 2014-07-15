#ifndef GRAPH_SEARCH_BFS_HPP
#define GRAPH_SEARCH_BFS_HPP
#include "search.hpp"
#include<queue>
namespace graph
{
    template<typename GraphType>
    class Queue
    {
    public:
        typedef typename GraphType::EdgeType E;
        typedef typename GraphType::VertexType V;
        
        Queue(std::map<V,typename edge_traits<E>::DistanceType>&){}
        void put(V t)
        {
            data.push(t);
        }
        V get()
        {
            V result=data.front();
            data.pop();
            return result;
        }
        bool empty()
        {
            return data.empty();
        }
    private:
        std::queue<V> data;
    };
    
    template<typename G>
    using BreadthFirstSearch=Search<G,Queue,DefaultSearch>;
    
}
#endif