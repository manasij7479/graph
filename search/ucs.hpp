#ifndef GRAPH_SEARCH_UFS_HPP
#define GRAPH_SEARCH_UFS_HPP
#include "search.hpp"
#include <queue>
#include <vector>
namespace graph
{
    template<typename GraphType>
    class PriorityQueue
    {
    public:
        typedef typename GraphType::EdgeType E;
        typedef typename GraphType::VertexType V;
        typedef typename std::map<V,typename edge_traits<E>::DistanceType> MapType;
        PriorityQueue(MapType& m):pq(m){}
        void put(V t)
        {
            pq.push(t);
        }
        V get()
        {
            V result=pq.top();
            pq.pop();
            return result;
        }
        bool empty()
        {
            return pq.empty();
        }
        
        template<typename GT>
        class Cmp
        {
        public:
            typedef typename GT::EdgeType E;
            typedef typename GT::VertexType V;
            typedef typename std::map<V,typename edge_traits<E>::DistanceType> MapType;
            
            Cmp(MapType& m):map(m){};
            bool operator()(V x,V y){return map[x]>map[y];}
            
        private:
            MapType& map;
        };
    private:
        std::priority_queue<V,std::vector<V>,Cmp<GraphType>>  pq;
    };
    
    template<typename G>
    using UniformCostSearch=Search<G,PriorityQueue,DefaultSearch>;
    
}
#endif