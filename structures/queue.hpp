#ifndef GRAPH_STRUCTURES_QUEUE
#define GRAPH_STRUCTURES_QUEUE
#include <queue>
#include <vector>
#include <set>
#include <functional>
#include <algorithm>
#include "distance.hpp"
namespace graph
{
    template<typename GraphType>
    class Queue
    {
    public:
        typedef typename GraphType::EdgeType E;
        typedef typename GraphType::VertexType V;
        
        Queue(std::function<bool(V,V)>){}
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
    
    //FIXME: Stupid linear implementation
    //Implement a min heap or use Boost's implementation
    //http://www.boost.org/doc/libs/1_56_0/doc/html/boost/heap/fibonacci_heap.html
    template<typename GraphType>
    class PriorityQueue
    {
    public:
        typedef typename GraphType::EdgeType E;
        typedef typename GraphType::VertexType V;
        PriorityQueue(std::function<bool(V,V)> compare):less(compare){}
        void put(V t)
        {
            data.push_back(t); 
//             std::push_heap(data.begin(),data.end(),less);
        }
        V get()
        {
//             std::pop_heap(data.begin(),data.end(),less);
            auto it = std::min_element(data.begin(),data.end(),less);
            V result=*it;
            data.erase(it);
//             data.pop_back();
            return result;
        }
        
        bool empty()
        {
            return data.empty();
        }
        
        bool isElement(V t)
        {
            return std::find(data.begin(),data.end(),t)!=data.end();
        }
        
    private:
        std::vector<V> data;
        std::function<bool(V,V)> less;
    };
}
#endif