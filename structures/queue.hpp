#ifndef GRAPH_STRUCTURES_QUEUE
#define GRAPH_STRUCTURES_QUEUE
#include <queue>
#include <vector>
#include <set>
#include "distance.hpp"
namespace graph
{
    template<typename GraphType>
    class Queue
    {
    public:
        typedef typename GraphType::EdgeType E;
        typedef typename GraphType::VertexType V;
        
        Queue(DistanceArray<GraphType>&){}
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
        PriorityQueue(DistanceArray<GraphType>& dist):pq(dist){}
        void put(V t)
        {
            pq.push(t); 
            elements.insert(t);
        }
        V get()
        {
            V result=pq.top();
            pq.pop();
            elements.erase(result);
            return result;
        }
        bool empty()
        {
            return pq.empty();
        }
        
        bool isElement(V t)
        {
            return elements.find(t)!=elements.end();
        }
        
        template<typename GT>
        class Cmp
        {
        public:
            typedef typename GT::EdgeType E;
            typedef typename GT::VertexType V;
            
            Cmp(DistanceArray<GT>& m):map(m){};
            bool operator()(V x,V y){return map[x]>map[y];}
            
        private:
            DistanceArray<GraphType>& map;
        };
    private:
        std::priority_queue<V,std::vector<V>,Cmp<GraphType>>  pq;
        std::set<V> elements;
    };
}
#endif