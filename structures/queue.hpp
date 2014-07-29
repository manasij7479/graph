#ifndef GRAPH_STRUCTURES_QUEUE
#define GRAPH_STRUCTURES_QUEUE
#include <queue>
#include <vector>
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
}
#endif