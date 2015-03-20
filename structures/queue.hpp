/**
* \brief - queue.hpp - Header file that has a collection of all queue related datastructures
* **/
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
        /**
         * \brief - function to insert element to queue
         * 
         * @param V t - Parameter, a vertex
         * **/
        void put(V t)
        {
            data.push(t);
        }
        /**
         * \brief - function to delete element from queue
         * 
         * @returns V result - a vertex
         * **/
        V get()
        {
            V result=data.front();
            data.pop();
            return result;
        }
        /**
         * \brief - function to check of queue is empty
         * **/
        bool empty()
        {
            return data.empty();
        }
    private:
        std::queue<V> data;
    };
    /**
     * \brief - class to implement priority queue
     * 
     * In priority queue, every value has a priority and they are deleted
     * from and inserted in the queue depending on the priority.
     * **/
    template<typename GraphType>
    class PriorityQueue
    {
    public:
        typedef typename GraphType::EdgeType E;
        typedef typename GraphType::VertexType V;
        PriorityQueue(std::function<bool(V,V)> compare):less(compare) {}
        /**
         * \brief - function to build a heap
         * **/
        PriorityQueue(std::function<bool(V,V)> compare, std::vector<V> data_):less(compare),data(data_)
        {
            for(int i=data.size()/2;i>=0;--i)
                siftDown(i);
        }
		/**
		 * \brief - function to insert element to priority queue depnding on priority
		 * 
		 * @param V t- Parameter, a vertex
		 * **/
        void put(V t)
        {
            data.push_back(t); 
            siftUp(data.size()-1);
        }
        /**
         * \brief - function to delete data from priority quque depending on priority
         * 
         * @returns result - a vetex
         * **/
        V get()
        {
            std::swap(data[0],data[data.size()-1]);
            auto result=data.back();
            data.pop_back();
            siftDown(0);
            return result;
        }
        /**
         * \brief - function to check if priority queue is empty or not
         * **/
        bool empty()
        {
            return data.empty();
        }
        /**
         * \brief - function to check if a vertex is already present in priority queue or not
         * 
         * @param V t - Parameter, a vertex
         * **/
        bool isElement(V t)
        {
            return std::find(data.begin(),data.end(),t)!=data.end();
        }
        /**
         * \brief - resturns the number of elements in priority queue
         * **/
        int size() { return data.size();}
        /**
         * \brief - function to construct a heap
         * **/
        void heapify()
        {
			for(int i=data.size()/2;i>=0;--i)
                siftDown(i);
		}
    
    private:
        /**
         * \brief - moves an element down the heap
         * 
         * the element 'x' is moved down the heap by 1 level until it reaches the correct postion
         * 
         * @param uint x - Parameter, a vertex number
         * **/
        void siftDown(uint x)
        {
            uint smallest=x,r=right(x),l=left(x); 
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
        /**
         * \brief -moves an element up the heap
         * 
         * the element 'x' is moved up the heap by 1 level until it reaches the correct position
         * 
         * @param int x - Parameter, a vertex number
         * **/
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
