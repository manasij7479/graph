#ifndef GRAPH_SEARCH_DFS_HPP
#define GRAPH_SEARCH_DFS_HPP
#include "search.hpp"
namespace graph
{
    template<typename T>
    class Stack
    {
    public:
        Stack(std::map<T,typename edge_traits<T>::DistanceType>&){}
        void put(T t)
        {
            data.push_back(t);
        }
        T get()
        {
            T result=data.back();
            data.pop_back();
            return result;
        }
        bool empty()
        {
            return data.empty();
        }
    private:
        std::vector<T> data;
    };
    
    template<typename T>
    using DepthFirstSearch=Search<T,Stack>;
    
}
#endif