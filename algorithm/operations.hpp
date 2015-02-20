/**	\brief operations.hpp - Header file that has collection of operations possible on any graph 
 * datastruture 
 * **/

#ifndef GRAPH_ALGORITHM_OPERATIONS_HPP
#define GRAPH_ALGORITHM_OPERATIONS_HPP
#include "predicates.hpp"
#include "collections.hpp"
#include "../graph.hpp"
#include <cmath>
#include<string>
namespace graph
{
    /**
     * \brief - Returns union of two Graph datastructures
     * 
     * Graph g1 - First parameter, a graph datastructure
     *   
     * Graph g2 - Second parameter, a graph datastructure
     * 
     * Graph result - Variable to store resultant Union of Graph g1 and Graph g2
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
     * Graph g1 - First parameter, a graph datastructure
     * 
     * Graph g2 - Second parameter, a graph datastructure
     * 
     * Graph result - Variable to store resultant intersection of Graph g1 and Graph g2
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
     * Graph g1 - First parameter, a graph datastructure
     * 
     * Graph g2 - Second parameter, a graph datastructure
     * 
     * Graph result - Variable to store resultant natural join of Graph g1 and Graph g2
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
     * Graph g1 - First parameter, a graph datastructure
     * 
     * Graph g2 - Second parameter, a graph datastructure
     * 
     * Graph result - Variable to store resultant symmetric_difference of Graph g1 and Graph g2
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
     * \brief - Returns cartesian_product of two Graph datastructures
     * 
     * Graph g1 - First parameter, a graph datastructure
     * 
     * Graph g2 - Second parameter, a graph datastructure
     * 
     * Graph result - Variable to store resultant cartesian_product of Graph g1 and Graph g2
     * **/
    int pairCompute(int x, int y)
    {
        return (x+y)*(x+y+1)/2+y;
    }
    std::pair<int, int> pairInvert(int z)
    {
        int w = (std::sqrt(8*z+1)-1)/2;
        int t = (w*w+w)/2;
        int y = z-t;
        int x = w-y;
        return {x, y};
    }
    template<typename Graph>
    Graph cartesian_product(Graph g1,Graph g2)
    {
        Graph result;
        for(auto i=g1.begin();i!=g1.end();++i)
            for(auto j=g2.begin();j!=g2.end();++j)
                result.insertVertex(pairCompute(i->first, j->first));
        for(auto i=result.begin();i!=result.end();++i)
            for(auto j=result.begin();j!=result.end();++j)
                if(i->first!=j->first)
                {
                    auto invi = pairInvert(i->first);
                    auto invj = pairInvert(j->first);
                    if((invi.first == invj.first && isAdjacent(g2,invi.second , invj.second )) 
                        || ( invi.second ==  invj.second && isAdjacent(g1, invi.first, invj.first)))
                        if(!isAdjacent(result,i->first,j->first))
                            result.insertEdge(i->first,j->first,1);
                }
        return result;
    }
    /**
     * \brief - Returns complement of a Graph datastructure
     * 
     * The edges not present in Graph g1 are present in graph result and vice versa
     * 
     * Graph g1 - Parameter, a graph datastructure
     * 
     * Graph result - Variable to store resultant complement of Graph g1
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
     * \brief - Returns the graph after deleting the edge between
     * vertex x and vertex y of graph g1
     * 
     * Graph g1 - Parameter, a graph datastructure
     * **/
    template<typename Graph>
    Graph EdgeDeletionSubgraph(Graph g1, typename Graph::VertexType x, typename Graph::VertexType  y)
    {
        g1.removeEdge(x,y);
                
        return g1;
    }
     /**
     * \brief - Returns the graph after deleting the vertex x 
     * of graph g1
     * 
     * Graph g1 - Parameter, a graph datastructure
     * **/
    template<typename Graph>
    Graph VertexDeletionSubgraph(Graph g1, typename Graph::VertexType x)
    {
        g1.removeVertex(x);
                
        return g1;
    }
    
    
     /**
     * \brief - Returns the graph minor after contracting the edge (x,y) 
     * of graph g
     * 
     * Graph g - Parameter, a graph datastructure
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
    
}
#endif
