#ifndef GRAPH_UTIL_VISITORS_HPP
#define GRAPH_UTIL_VISITORS_HPP
#include "../graph.hpp"
#include <functional>

namespace graph
{
    template<typename Graph>
    void VisitVertices(Graph& g, std::function<void(typename Graph::VertexType)> f)
    {
        for(auto it = g.begin(); it != g.end(); ++it)
            f(it->first);
    }
    
    template<typename Graph>
    void VisitNeighbours(Graph& g, typename Graph::VertexType v, std::function<void(typename Graph::VertexType)> f)
    {
        for(auto it = g.nbegin(v); it != g.nend(v); ++it)
            f(it->first);
    }
    
    //Especially useful if the compiler is very good at optimizing lambda functions
    template<typename Graph>
    void VisitEdges(Graph& g, std::function<void(typename Graph::VertexType,typename Graph::VertexType)> f)
    {
        VisitVertices
        (g, 
            [&g,&f](typename Graph::VertexType x)
            {
                VisitNeighbours
                (
                    g,x,
                    [&g,&f,&x](typename Graph::VertexType y){f(x,y);}
                );
            }
        );
    }
}
#endif