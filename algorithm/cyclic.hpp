#ifndef GRAPH_ALGORITHM_CYCLIC_HPP
#define GRAPH_ALGORITHM_CYCLIC_HPP
#include "../graph.hpp"
#include "../search/search.hpp"
#include "../search/dfs.hpp"
#include "../util/io.hpp"
#include "predicates.hpp"

#include <iostream>
namespace graph
{
    template
    <
        typename Graph,
        template <typename > class Container = Stack
    >
    class IsCyclic : public Search<Graph,Container,IsCyclic>
    {
        typedef typename Graph::VertexType V;
        typedef Search<Graph,Container,IsCyclic> Base;
    public:
        IsCyclic(Graph& g_,const V& s):Search<Graph,Container,IsCyclic>(g_,s),cyclic(false){}
        bool p3(V v)
        {
            cyclic=true;
            return false;
        }
        bool check()
        {
            Base::execute();
            return cyclic;
        }
    private:
        bool cyclic;
    };
    template<typename Graph>
    bool isCyclic(Graph& g)
    {
        IsCyclic<Graph> searchObject(g,g.begin()->first);
        return searchObject.check();
    }
}
#endif 