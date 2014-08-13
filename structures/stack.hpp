#ifndef GRAPH_STRUCTURES_STACK
#define GRAPH_STRUCTURES_STACK
#include <stack>
#include "distance.hpp"
#include <functional>
namespace graph
{
    template<typename GraphType>
    class Stack
    {
    public:
        typedef typename GraphType::EdgeType E;
        typedef typename GraphType::VertexType V;
        
        Stack(std::function<bool(V,V)>){}
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
        int count(V v)
        {
            return data.count(v);
        }
    private:
        std::vector<V> data;
    };
    
}
#endif