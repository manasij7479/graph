#ifndef GRAPH_UTIL_VISITORS_HPP
#include "../graph.hpp"
#include <functional>
#define GRAPH_UTIL_VISITORS_HPP
/**
 * \brief visitors.hpp - Header file to store different traversal techniques
 * **/
 namespace graph
{
    template<typename Graph, typename F>
    /**
     * \brief - function to visit all vertices of a graph
     * 
     * @param Graph& g - First Parameter, a graph datastructure
     * 
     * @param F f - Second Parameter, a callback function
     * **/
    void VisitVertices(Graph& g, F f)
    {
        for(auto it = g.begin(); it != g.end(); ++it)
            f(it->first);
    }
    /**
     * \brief - function to visit all neighbours of a vertex of a graph
     * 
     * a neighbour of a vertex is another vertex which shares an edge
     * 
     * @param Graph& g - First Parameter, a graph datastructure
     * 
     * @param Graph::VertexType v - Second Parameter, a vertex
     * 
     * @param F f - Third Parameter, a callback function
     * **/
    template<typename Graph, typename F>
    void VisitNeighbours(Graph& g,typename Graph::VertexType v, F f)
    {
        for(auto it = g.nbegin(v); it != g.nend(v); ++it)
            f(it->first);
    }
    /**
     * \brief - function to visit all edges of a graph
     * 
     * @param Graph& g - First Parameter, a graph datastructure
     * 
     * @param F f - Second Parameter, a callback function
     * **/
    //Especially useful if the compiler is very good at optimizing lambda functions
    template<typename Graph, typename F>
    void VisitEdges(Graph& g, F f)
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
