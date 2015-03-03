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
    
    template<typename GraphType>
    class PriorityQueue
    {
    public:
        typedef typename GraphType::EdgeType E;
        typedef typename GraphType::VertexType V;
        PriorityQueue(std::function<bool(V,V)> compare, std::vector<V> data_):less(compare),data(data_)
        {
            for(int i=data.size()/2;i>0;--i)
                siftDown(i);
        }

        void put(V t)
        {
            data.push_back(t); 
            siftUp(data.size()-1);
        }
        
        V get()
        {
            std::swap(data[0],data[data.size()-1]);
            auto result=data.back();
            data.pop_back();
            siftDown(0);
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
        
        int size() { return data.size();}
    
    private:
        
        void siftDown(int x)
        {
            int smallest=x,r=right(x),l=left(x); 
            if(l<data.size() && less(data[l],data[smallest]))
                smallest=l;
            if(r<data.size() && less(data[r],data[smallest]))
                smallest=r;
            if(smallest!=x)
            {
                std::swap(data[smallest],data[x]);
                siftDown(smallest);
            }
        }
        void siftUp(int x)
        {
            int p=parent(x);
            if(p>=0 && less(data[x],data[p]))
            {
                std::swap(data[x],data[p]);
                siftUp(p);
            }
        }
        
        int left(int x) { return 2*x+1; }
        int right(int x) { return 2*x+2; }
        int parent(int x) { return x/2; }
        
        std::vector<V> data;
        std::function<bool(V,V)> less;
    };
}
#endif