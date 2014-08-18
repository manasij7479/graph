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
}
#endif