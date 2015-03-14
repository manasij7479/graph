/**	\brief enumeration.hpp - Header file that has collection of functions 
 * that can enumerate different aspects of a grah object
 * **/


#ifndef GRAPH_ALGORITHM_ENUMERATION_HPP
#define GRAPH_ALGORITHM_ENUMERATION_HPP    
#include "../graph.hpp"
#include "collections.hpp"
#include "../structures/disjointset.hpp"
#include <set>
namespace graph
{
    /** \brief - Returns number of edges in Graph g
     * 
     * @param Graph g - Parameter, a graph object
     * **/
    template<typename Graph>
    int Size(Graph& g)
    {
        return EdgeList(g,false).size();
    }
    
    /** \brief - Returns the number of edges directed out of Graph::VertexType v in Graph g
     * 
     * @param Graph g - First parameter, a graph object
     * 
     * @param Graph::VertexType v - Second parameter, a vertex of Graph g
     * 
     * @returns int conunt - the number of edges directed out of Graph::VertexType v in Graph g
     * **/
    
    template<typename Graph>
    int outDegree(Graph& g, typename Graph::VertexType v)
    {
        int count=0;
        for(auto i=g.nbegin(v);i!=g.nend(v);++i)
            count++;
        return count;
    }
    
    /** \brief - Returns the number of edges directed towards Graph::VertexType v in Graph g
     * 
     * @param Graph g - First parameter, a graph object
     * 
     * @param Graph::VertexType v - Second parameter, a vertex of Graph g
     * 
     * @returns int conunt - the number of edges directed towards Graph::VertexType v in Graph g
     * **/
    
    template<typename Graph>
    int inDegree(Graph& g, typename Graph::VertexType v)
    {
        int count=0;
        if(!g.isDirected())
            return outDegree(g,v);
        else
        {
            for(auto x=g.begin();x!=g.end();++x)
            {
                for(auto y=g.nbegin(x->first);y!=g.nend(x->first);++y)
                    if(y->first==v)
                        count++;
            }
            return count;
        }
    }
    
    /** \brief - Returns the total number of edges of Graph::VertexType v in Graph g
     * 
     * @param Graph g - First parameter, a graph object
     * 
     * @param Graph::VertexType v - Second parameter, a vertex of Graph g
     * 
     * @returns the total number of edges of Graph::VertexType v in Graph g
     * **/
    
    template<typename Graph>
    int degree(Graph& g,typename Graph::VertexType v)
    {
        if(!g.isDirected())
            return outDegree(g,v);
        else
            return inDegree(g,v)+outDegree(g,v);
    }
    
    /** \brief - Returns the degree of each vertex in Graph g if degree of all vertex is equal,
     * returns 0 otherwise
     * 
     * @param Graph g - Parameter, a graph object
     * 
     * @returns int k - the degree of each vertex in Graph g if degree of all vertex is equal
     * @returns 0 otherwise
     * **/
    
    template<typename Graph>
    int nregular(Graph& g)
    {
        int k=degree(g,g.begin()->first);
        for(auto x=g.begin();x!=g.end();x++)
        {
            if (k!=degree(g,x->first))
                return 0;
        }
        return k;
    }
    
    /** \brief - Returns the radius eccentricity in Graph g
     * 
     * Radius eccentricity is the minimum eccecntricity if a graph
     * 
     * @param Graph g - Parameter, a graph object
     * 
     * @returns min- minimum eccentricity
     * **/
    
    template<typename Graph>
    typename Graph::EdgeType Radius(Graph& g)
    {
        auto e=EcentricityList(g);
        auto min=e.begin()->second;
        for(auto i=e.begin();i!=e.end();++i)
                if(i->second<min)
                    min=i->second;
        return min;
    }
    
    /** \brief - Returns the diameter of Graph g
     * 
     * Diameter of a graph is the maximum eccentricity of a graph
     * 
     * @param Graph g - Parameter, a graph object
     * 
     * @returns max - maximum eccentricity of a graph
     * **/
    
    template<typename Graph>
    typename Graph::EdgeType Diameter(Graph& g)
    {
        auto e=EcentricityList(g);
        auto max=e.begin()->second;
        for(auto i=e.begin();i!=e.end();++i)
                if(i->second>max)
                    max=i->second;
        return max;
    }
    
    /** \brief - Returns the density of edges with respect to vertices in Graph g
     * 
     * Density of a graph is obtained by the formula
     * 2*no of edges in graph / (no of vertices of a graph * no of vertices of a graph - 1)
     * 
     * @param Graph g - Parameter, a graph object
     * **/
    
    template<typename Graph>
    float Density(Graph& g)
    {
        return (2.0*Size(g))/(g.order()*(g.order()-1));
    }
    
    /**
     * \brief -  Returns the number of connected components of a graph
     * 
     * Connected Components of a graph are subgraphs which are connected.
     * A pair of vertices are connected if there exists a path between them in a graph.
     * 
     * @param Graph g - Parameter, a graph object
     * **/
    
    template<typename Graph>
    int noOfComponents(Graph g)
    {
        DisjointSet<Graph> ds(g);
        for(auto i=g.begin();i!=g.end();++i)
            for(auto j=g.nbegin(i->first);j!=g.nend(i->first);++j)
                ds.Union(i->first,j->first);
        std::set<typename Graph::VertexType> s;
        for(auto i=g.begin();i!=g.end();++i)
            s.insert(ds.findRoot(i->first));
        return s.size();
    }
}
#endif
