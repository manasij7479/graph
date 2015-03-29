#ifndef GRAPH_ALGORITHM_OPERATIONS_HPP
#define GRAPH_ALGORITHM_OPERATIONS_HPP
#include "predicates.hpp"
#include "collections.hpp"
#include "../graph.hpp"
#include <cmath>
#include<string>
/**	\brief operations.hpp - Header file that has collection of operations possible on any graph 
 * datastruture 
 * **/
namespace graph
{
    /**
     * \brief - Returns union of two Graph datastructures
     * 
     * A union of two graphs contains all the vertices of both graphs and all
     * corresponding edges from both graphs.
     * 
     * @param Graph g1 - First parameter, a graph datastructure
     *   
     * @param Graph g2 - Second parameter, a graph datastructure
     * 
     * @returns Graph result - Variable to store resultant Union of Graph g1 and Graph g2
     * **/
    template<typename Graph>
    Graph Union(Graph g1,Graph g2)
    {
        Graph result;
        for(auto i=g1.begin();i!=g1.end();++i)
            result.insertVertex(i->first);
        for(auto i=g2.begin();i!=g2.end();++i)
            result.insertVertex(i->first);
        for(auto i=g1.begin();i!=g1.end();++i)
            for(auto j=g1.nbegin(i->first);j!=g1.nend(i->first);++j)
                result.insertEdge(i->first,j->first,j->second);
        for(auto i=g2.begin();i!=g2.end();++i)
            for(auto j=g2.nbegin(i->first);j!=g2.nend(i->first);++j)
                if(!isAdjacent(result,i->first,j->first))
                    result.insertEdge(i->first,j->first,j->second);
                        
        return result;
    }
    
    /**
     * \brief - Returns intersection of two Graph datastructures
     * 
     * An intersection of two graphs contains the vertices common to both graphs
     * and corresponding edges from both graphs.
     * 
     * @param Graph g1 - First parameter, a graph datastructure
     * 
     * @param Graph g2 - Second parameter, a graph datastructure
     * 
     * @returns Graph result - Variable to store resultant intersection of Graph g1 and Graph g2
     * **/
    template<typename Graph>
    Graph intersection(Graph g1,Graph g2)
    {
        Graph result;
        for(auto i=g1.begin();i!=g1.end();++i)
            if(isVertex(g2,i->first))
                result.insertVertex(i->first);
        for(auto i=result.begin();i!=result.end();++i)
            for(auto j=g1.nbegin(i->first);j!=g1.nend(i->first);++j)
                if(isAdjacent(g2,i->first,j->first))
                    if(!isAdjacent(result,i->first,j->first))
                        result.insertEdge(i->first,j->first,1);
                        
        return result;
    }
    /**
     * \brief - Returns natural join of two Graph datastructures
     * 
     * A natural join of two graphs is a union of two graphs with some additional edges.
     * The additional edges joins all vertices of first graph with all vertices of second graph.
     * 
     * @param Graph g1 - First parameter, a graph datastructure
     * 
     * @param Graph g2 - Second parameter, a graph datastructure
     * 
     * @returns Graph result - Variable to store resultant natural join of Graph g1 and Graph g2
     * **/
    template<typename Graph>
    Graph join(Graph g1,Graph g2)
    {
        Graph result=Union(g1,g2);
        for(auto i=g1.begin();i!=g1.end();++i)
            for(auto j=g2.begin();j!=g2.end();++j)
                result.insertEdge(i->first,j->first,1);
         
        return result;
    }
    /**
     * \brief - Returns symmetric_difference of two Graph datastructures
     * 
     * Symmetric difference of two graphs contains the vertices present in first graph and not
     * in second graph and vice versa. It contains the edges that connect two vertices of first
     * graph that are not connected by an edge in the second graph and vice versa.
     * 
     * @param Graph g1 - First parameter, a graph datastructure
     * 
     * @param Graph g2 - Second parameter, a graph datastructure
     * 
     * @returns Graph result - Variable to store resultant symmetric_difference of Graph g1 and Graph g2
     * **/
    template<typename Graph>
    Graph symmetric_difference(Graph g1,Graph g2)
    {
        Graph result;
        for(auto i=g1.begin();i!=g1.end();++i)
            if(!isVertex(g2,i->first))
                result.insertVertex(i->first);
        for(auto i=g2.begin();i!=g2.end();++i)
            if(!isVertex(g1,i->first))
                result.insertVertex(i->first);
        
        for(auto i=g1.begin();i!=g1.end();++i)
            for(auto j=g1.nbegin(i->first);j!=g1.nend(i->first);++j)
                if(isVertex(result,i->first) && isVertex(result,j->first))
                    if(!isAdjacent(g2,i->first,j->first))
                        result.insertEdge(i->first,j->first,j->second);
        for(auto i=g2.begin();i!=g2.end();++i)
            for(auto j=g2.nbegin(i->first);j!=g2.nend(i->first);++j)
                if(isVertex(result,i->first) && isVertex(result,j->first))
                    if(!isAdjacent(g1,i->first,j->first))
                        result.insertEdge(i->first,j->first,j->second);
                    
        return result;
    }
    /**
     * \brief - returns the result of function (x+y) *(x+y+1) / 2 +y
     * 
     * @param int x - First Parameter
     * 
     * @param int y - Second Parameter
     * 
     * @returns (x+y) *(x+y+1) / 2 +y
     * **/
    inline int pairCompute(int x, int y)
    {
        return (x+y)*(x+y+1)/2+y;
    }
    /**
     * \brief - returns a pair (square root of(8*z+1)-1)/2 - y and z - (w*w+w)/2
     * 
     * @param int z - Parameter
     * 
     * @returns (square root of(8*z+1)-1)/2 - y and z - (w*w+w)/2
     * **/
    inline std::pair<int, int> pairInvert(int z)
    {
        int w = (std::sqrt(8*z+1)-1)/2;
        int t = (w*w+w)/2;
        int y = z-t;
        int x = w-y;
        return {x, y};
    }
    /**
     * \brief - Returns cartesian_product of two Graph datastructures
     * 
     * The set of vertices of cartesian product of two graphs conatins the product of vertices
     * of the two graphs. Two vertices (u,u') and (v,v') are connected by and edge in the
     * cartesian product iff either u = v and u' is adjacent with v' in first graph or 
     * u' = v' and u is adjacent with v in second graph.
     * 
     * @param Graph g1 - First parameter, a graph datastructure
     * 
     * @param Graph g2 - Second parameter, a graph datastructure
     * 
     * @returns Graph result - Variable to store resultant cartesian_product of Graph g1 and Graph g2
     * **/
    template<typename Graph>
    Graph cartesian_product(Graph g1,Graph g2)
    {
        Graph result;
        std::map<int,int> vmap;
        int counter = 1;
        for(auto i=g1.begin();i!=g1.end();++i)
            for(auto j=g2.begin();j!=g2.end();++j)
                vmap[pairCompute(i->first, j->first)] = counter++;
        for(auto i=vmap.begin();i!=vmap.end();++i)
            result.insertVertex(i->second);
        for(auto i=vmap.begin();i!=vmap.end();++i)
            for(auto j=vmap.begin();j!=vmap.end();++j)
                if(i->second!=j->second)
                {
                    auto invi = pairInvert(i->first);
                    auto invj = pairInvert(j->first);
                    if((invi.first == invj.first && isAdjacent(g2,invi.second , invj.second )) 
                        || ( invi.second ==  invj.second && isAdjacent(g1, invi.first, invj.first)))
                        if(!isAdjacent(result,i->second,j->second))
                            result.insertEdge(i->second,j->second,1);
                }
        return result;
    }
    
    /**
     * \brief - Returns complement of a Graph datastructure
     * 
     * The edges not present in Graph g1 are present in graph result and vice versa
     * 
     * @param Graph g1 - Parameter, a graph datastructure
     * 
     * @returns Graph result - Variable to store resultant complement of Graph g1
     * **/
    template<typename Graph>
    Graph complement(Graph g1)
    {
        Graph result;
        for(auto i=g1.begin();i!=g1.end();++i)
            result.insertVertex(i->first);
        for(auto i=g1.begin();i!=g1.end();++i)
            for (auto j=g1.begin();j!=g1.end();++j)
                if(i->first!=j->first && !(isAdjacent(g1,i->first,j->first)))
                    result.insertEdge(i->first,j->first,1);
                
        return result;
    }
    /**
     * \brief - Returns the graph after deleting the edge between vertex x and vertex y 
     * of graph g1
     * 
     * @param Graph g1 - First Parameter, a graph datastructure
     * 
     * @param typename Graph::VertexType x - Second Parameter, a vertex
     * 
     * @param typename Graph::VertexType y - Third Parameter, a vertex
     * 
     * @returns g1 - the graph after deleting the edge (x,y) of graph g
     * **/
    template<typename Graph>
    Graph EdgeDeletionSubgraph(Graph g1, typename Graph::VertexType x, typename Graph::VertexType  y)
    {
        g1.removeEdge(x,y);
                
        return g1;
    }
     /**
     * \brief - Returns the graph after deleting the vertex x of graph g1
     * 
     * @param Graph g1 - Parameter, a graph datastructure
     * 
     * @param typename Graph::VertexType x - Second Parameter, a vertex
     * 
     * @returns g1 - the graph after removing vertex x
     * **/
    template<typename Graph>
    Graph VertexDeletionSubgraph(Graph g1, typename Graph::VertexType x)
    {
        g1.removeVertex(x);
        return g1;
    }
    
    
     /**
     * \brief - Returns the graph minor after contracting the edge (x,y) of graph g
     * 
     * Edge contraction removes an edge joning x and y, and merges the vertices x and y
     * 
     * @param Graph g - First Parameter, a graph datastructure
     * 
     * @param typename Graph::VertexType x - Second Parameter, a vertex
     * 
     * @param typename Graph::VertexType y - Third Parameter, a vertex
     * 
     * @returns g - the graph minor after contracting the edge (x,y) of graph g
     * **/
    template<typename Graph>
    Graph EdgeContractionMinor(Graph g, typename Graph::VertexType x, typename Graph::VertexType  y)
    {
        if (g.isDirected())
            throw std::runtime_error("Operation not yet supported for directed graphs.");
        if (!isAdjacent(g,x,y))
            return g;//this is not vertex identification
        g.removeEdge(x,y);
        for (auto v : OutVertexList(g,y))
            g.insertEdge(x,v,g.weight(y,v));
        
        g.removeVertex(y);
        
        return g;
    }
    
     /**
     * \brief - Returns line graph of a Graph datastructure
     * 
     * - each vertex of L(G) represents an edge of G, 
     * - two vertices of L(G) are adjacent if and only if 
     * their corresponding edges share a common endpoint in G.
     * 
     * @param Graph g1 - Parameter, a graph datastructure
     * 
     * @returns Graph result - Variable to store resultant line graph of Graph g1
     * **/
    template<typename Graph>
    Graph line(Graph g)
    {
        Graph result;
        auto elist = EdgeList(g,false);
        for(auto i=elist.begin();i!=elist.end();++i)
            result.insertVertex(pairCompute(std::get<0>(*i),std::get<1>(*i)));
        for(auto i=result.begin();i!=result.end();++i)
            for(auto j=result.begin();j!=result.end();++j)
                if(i->first != j->first)
                {
                    auto invi=pairInvert(i->first);
                    auto invj=pairInvert(j->first);
                    if
                    (
                        invi.first == invj.first ||
                        invi.first == invj.second ||
                        invi.second == invj.second ||
                        invi.second == invj.first
                    )
                        result.insertEdge(i->first,j->first,1);
                }
        return result;
    }
    
}
#endif
