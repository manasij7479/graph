/**	\brief collection.hpp - Header file that has functions that returns sequences and lists of
 *  different aspects of a graph object
 * **/

#ifndef GRAPH_ALGORITHM_COLLECTIONS_HPP
#define GRAPH_ALGORITHM_COLLECTIONS_HPP
#include "../graph.hpp"
#include "../util/visitors.hpp"
#include "search.hpp"
#include "enumeration.hpp"
#include "predicates.hpp"
#include "../structures/attribute.hpp"
#include "coloring.hpp"
#include<vector>
#include<map>
#include<set>
#include<tuple>
#include<algorithm>
#include<stdexcept>
#include<utility>

namespace graph
{
	/**
     * \brief - Returns a list containing names of all the vertices in Graph g
     * 
     * @param Graph g - Parameter, a graph object
     *   
     * @returns vector<typename Graph::VertexType> v - vector to store the list
     * **/
     
    template<typename Graph>
    std::vector<typename Graph::VertexType> VertexList(Graph& g)
    {
        std::vector<typename Graph::VertexType> v;
        VisitVertices(g,[&v](typename Graph::VertexType x){v.push_back(x);}); // put auto after enabling c++11
        return v;
    }
    
    /**
     * \brief - Returns a list containing of adjacent vertices with edge weights
     * 
     * This function returns a list containing pairs of vertices which are connected by an edge.
     * The list also contains the edge weights for each edge.
     * 
     * @param Graph g - First parameter, a graph object
     * 
     * @param bool duplicate - Second parameter, to check for duplicate edges
     *   
     * @returns vector<std::tuple<typename Graph::VertexType,typename Graph::VertexType,typename Graph::EdgeType>> e - vector to store the list
     * **/
     
    template<typename Graph>
    std::vector
    <
        std::tuple
        <
            typename Graph::VertexType,
            typename Graph::VertexType,
            typename Graph::EdgeType
        >
    >
    EdgeList(Graph& g,bool duplicate=true)
    {
        std::vector<std::tuple<typename Graph::VertexType,typename Graph::VertexType,typename Graph::EdgeType>> e;
        for(auto i=g.begin();i!=g.end();++i)
            for(auto j=g.nbegin(i->first);j!=g.nend(i->first);++j)
                if(!g.isDirected()&& !duplicate)
                {
                    if(std::find(e.begin(),e.end(),std::make_tuple(j->first,i->first,j->second))==e.end())
                        e.push_back(std::make_tuple(i->first,j->first,j->second));
                }
                else
                    e.push_back(std::make_tuple(i->first,j->first,j->second));
        return e;
    }
    /**
     * 	\brief - A function to compare the edges between two vertices
     * **/
    
    template <typename Graph>
    bool sortComparison
    (
        std::tuple
        <   
            typename Graph::VertexType,
            typename Graph::VertexType,
            typename Graph::EdgeType
        > a,
        std::tuple
        <   
            typename Graph::VertexType,
            typename Graph::VertexType,
            typename Graph::EdgeType
        > b
    )
    {
        return (std::get<2>(a)<std::get<2>(b));
    }
    /**
     * \brief - eturns a list containing of adjacent vertices with edge weights
     * 
     * This function returns a list containing pairs of vertices which are connected by an edge.
     * The list also contains the edge weights for each edge. The list is sorted by edge weight
     * in ascending order.
     * 
     * 
     * @param Graph g - First Parameter, a graph object
     * 
     * @param bool duplicate - Second Parameter, to check for duplicate edges
     *   
     * @returns std::vector<std::tuple<typename Graph::VertexType,typename Graph::VertexType,typename Graph::EdgeType>> e - variable to store the sorted edge list
     * **/
    
    template <typename Graph>
    std::vector
    <
        std::tuple
        <
            typename Graph::VertexType,
            typename Graph::VertexType,
            typename Graph::EdgeType
        >
    >
    sortedEdgeList(Graph& g,bool duplicate=true)
    {
         std::vector<std::tuple<typename Graph::VertexType,typename Graph::VertexType,typename Graph::EdgeType>> e=EdgeList(g,duplicate);
         std::sort(e.begin(),e.end(),sortComparison<Graph>);
         return e;
    }
    
    /**
     * \brief - Returns a list containing all the vertices of Graph g
     * alongwith the total number of edges of each vertex
     * 
     * @param Graph g - Parameter, a graph object
     *   
     * @returns map<typename Graph::VertexType,int> m - variable to store the list
     * **/
     
    template<typename Graph>
    std::map<typename Graph::VertexType,int> DegreeList(Graph& g)
    {
        std::map<typename Graph::VertexType,int> m;
        for(auto i=g.begin();i!=g.end();++i)
            m[i->first]=degree(g,i->first);
        return m;
    }
    
    /**
     * \brief - Returns a sequence of total number of edges of all vertices in Graph g in sorted
     * order
     * 
     * The list is sorted in ascending order.
     * 
     * @param Graph g - Parameter, a graph object
     *   
     * @returns vector<int> ds - variable to store the sequence
     * **/
     
    template<typename Graph>
    std::vector<int> DegreeSequence(Graph& g)
    {
        std::vector<int> ds;
        for(auto i=g.begin();i!=g.end();++i)
            ds.push_back(degree(g,i->first));
        std::sort(ds.begin(),ds.end());
        return ds;
    }
    
    /**
     * \brief - Returns a map of all vertices in Graph g with their corresponding eccentricities
     * 
     * Eccentricity of a vertex is the maximum distance that can be covered starting from that
     * vertex in a linear acyclic path.
     * 
     * @param Graph g - Parameter, a graph object
     *   
     * @returns map<typename Graph::VertexType,typename Graph::EdgeType> m - variable to store the mapping
     * **/
    
    template<typename Graph>
    std::map<typename Graph::VertexType,typename Graph::EdgeType> EcentricityList(Graph& g)
    {
        if(g.isDirected() || !isConnected(g))
            throw std::runtime_error("Not Possible : 'g'-> Undirected & Connected not met ...");
        std::map<typename Graph::VertexType,typename Graph::EdgeType> m;
        for(auto i=g.begin();i!=g.end();++i)
        {
            UniformCostSearch<Graph> ucs(g,i->first);
            ucs();
            auto d = ucs.getDistanceArray();
            auto max = d[g.begin()->first];
            for(auto j = g.begin();j != g.end(); ++j)
                if(d[j->first] > max)
                    max = d[j->first];
             m[i->first] = max;
        }
        return m;
    }
    
     /**
     * \brief - Returns a set of vertices constituting the centre in Graph g
     * 
     * Centre of a graph is the set of vertices with minimum eccentricity.
     * 
     * @param Graph g - Parameter, a graph object
     *   
     * @returns set<typename Graph::VertexType> s - variable to store the centres
     * **/
    
    template<typename Graph>
    std::set<typename Graph::VertexType> Centre(Graph& g)
    {
        std::set<typename Graph::VertexType> s;
        auto e=EcentricityList(g);
        auto min=e.begin()->second;
        for(auto i=e.begin();i!=e.end();++i)
                if(i->second<min)
                    min=i->second;
        for(auto i=e.begin();i!=e.end();++i)
            if(min==i->second)
                s.insert(i->first);
        return s;
    }
    
     /**
     * \brief - Returns a set of vertices constituting the periphery in Graph g
     * 
     * Periphery is a set of vertices with the maximum eccentricity.
     * 
     * @param Graph g - Parameter, a graph object
     *   
     * @returns set<typename Graph::VertexType> s - variable to store the peripheries
     * **/
   
    
    template<typename Graph>
    std::set<typename Graph::VertexType> Periphery(Graph& g)
    {
        std::set<typename Graph::VertexType> s;
        auto e=EcentricityList(g);
        auto max=e.begin()->second;
        for(auto i=e.begin();i!=e.end();++i)
                if(i->second>max)
                    max=i->second;
        for(auto i=e.begin();i!=e.end();++i)
            if(max==i->second)
                s.insert(i->first);
        return s;
    }
   
    /**
     * \brief - Returns adjacency matrix of Graph g
     * 
     * The matrix is a mapping between the pair of vertices and the edge between 
     * these two vertices
     * 
     * @param Graph g - Parameter, a graph object
     *   
     * @returns map<std::pair<typename Graph::VertexType,typename Graph::VertexType>,typename Graph::EdgeType> m - variable to store the adjacency matrix
     * **/
       
    template<typename Graph>
    std::map<std::pair<typename Graph::VertexType,typename Graph::VertexType>,typename Graph::EdgeType> AdjacencyMatrix(Graph& g)
    {
        std::map<std::pair<typename Graph::VertexType,typename Graph::VertexType>,typename Graph::EdgeType> m;
        for(auto i=g.begin();i!=g.end();++i)
            for(auto j=g.nbegin(i->first);j!=g.nend(i->first);++j)
                m[std::make_pair(i->first,j->first)]=j->second;
        return m;
    }
    
    /**
     * \brief - Returns a list containing all the vertices of Graph g having edges 
     * originating from Vertex x
     * 
     * @param Graph g - First parameter, a graph object
     * 
     * @param typename Graph::VertexType x - Second parameter, a vertex of Graph g
     *   
     * @returns map<typename Graph::VertexType> v - variable to store the list
     * **/
    
    template<typename Graph>
    std::vector<typename Graph::VertexType> OutVertexList(Graph& g,typename Graph::VertexType x)
    {
        std::vector<typename Graph::VertexType> v;
        for(auto i=g.nbegin(x);i!=g.nend(x);++i)
            v.push_back(i->first);
        
        return v;
    }
    
    /**
     * \brief - Returns a list containing all vertices of Graph g having edges
     * ending at Vertex x
     * 
     * @param Graph g - Parameter, a graph object
     * 
     * @param typename Graph::VertexType x - Second parameter, a vertex of Graph g
     *   
     * @returns map<typename Graph::VertexType> v - variable to store the list
     * **/
    
    template<typename Graph>
    std::vector<typename Graph::VertexType> InVertexList(Graph& g,typename Graph::VertexType x)
    {
        if(!g.isDirected())
            return outVertexList(g,x);
        else
        {
            std::vector<typename Graph::VertexType> v;
            for(auto i=g.begin();i!=g.end();++i)
            {
                auto it=g.nfind(i->first,x);
                if(it!=g.nend(i->first))
                    v.push_back(i->first);
            }
            return v;
        }           
    }
    template<typename Graph>
    VertexAttribute<Graph, int> minVertexColorAssignment(Graph& g)
    {
        auto state = minVertexColoring(g);
        VertexAttribute<Graph, int> vattr(state.getColorMap());
        return vattr;
    }
}
#endif
