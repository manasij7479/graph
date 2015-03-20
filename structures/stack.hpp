/**
 * \brief -	stack.hpp - header file to implement stack datastructure 
 * **/
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
        /**
         * \brief - function to push element to stack
         * 
         * @param V t - Parameter, a vertex
         * **/
        void put(V t)
        {
            data.push_back(t);
        }
        /**
         * \brief - function to pop element from stack
         * 
         * @returns V result - a vertex
         * **/
        V get()
        {
            V result=data.back();
            data.pop_back();
            return result;
        }
        /**
         * \brief - checks if stack is empty
         * **/
        bool empty()
        {
            return data.empty();
        }
        /**
         * \brief - returns the number of element in stack
         * 
         * @param V v - Parameter, a vertex
         * **/
        int count(V v)
        {
            return data.count(v);
        }
    private:
        std::vector<V> data;
    };
    
}
#endif
