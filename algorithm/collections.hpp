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
     * Graph g - Parameter, a graph object
     *   
     * vector<typename Graph::VertexType> v - vector to store the list
     * **/
     
    template<typename Graph>
    std::vector<typename Graph::VertexType> VertexList(Graph& g)
    {
        std::vector<typename Graph::VertexType> v;
        VisitVertices(g,[&](typename Graph::VertexType x){v.push_back(x);}); // put auto after enabling c++11
        return v;
    }
    
    /**
     * \brief - Returns a list containing all pairs of vertices between which an edge
     * exists in Graph g, along with the edge weights
     * 
     * Graph g - First parameter, a graph object
     * 
     * bool duplicate - Second parameter, to check for duplicate edges
     *   
     * vector<std::tuple<typename Graph::VertexType,typename Graph::VertexType,typename Graph::EdgeType>> e - vector to store the list
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
     * \brief - Returns a list containing names of all the vertices in Graph g
     * alongwith the total number of edges of each vertex
     * 
     * Graph g - Parameter, a graph object
     *   
     * map<typename Graph::VertexType,int> m - variable to store the list
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
     * Graph g - Parameter, a graph object
     *   
     * vector<int> ds - variable to store the sequence
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
     * \brief - Returns a map of al vertices in Graph g with their corresponding eccentricities
     * 
     * Graph g - Parameter, a graph object
     *   
     * map<typename Graph::VertexType,typename Graph::EdgeType> m - variable to store the mapping
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
            auto d=ucs.getDistanceArray();
            auto max=d.begin()->second;
            for(auto j=d.begin();j!=d.end();++j)
                if(j->second>max)
                    max=j->second;
             m[i->first]=max;
        }
        return m;
    }
    
     /**
     * \brief - Returns a set of vertices constituting the centre in Graph g
     * 
     * Graph g - Parameter, a graph object
     *   
     * set<typename Graph::VertexType> s - variable to store the centres
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
     * Graph g - Parameter, a graph object
     *   
     * set<typename Graph::VertexType> s - variable to store the peripheries
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
     * as a mapping between the pair of vertices and the edge between these two vertices
     * 
     * Graph g - Parameter, a graph object
     *   
     * map<std::pair<typename Graph::VertexType,typename Graph::VertexType>,typename Graph::EdgeType> m - variable to store the adjacency matrix
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
     * \brief - Returns a list containing names of all the vertices in Graph g
     * having edges originating from Vertex x
     * 
     * Graph g - First parameter, a graph object
     * 
     * typename Graph::VertexType x - Second parameter, a vertex of Graph g
     *   
     * map<typename Graph::VertexType> v - variable to store the list
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
     * \brief - Returns a list containing names of all the vertices in Graph g
     * having edges ending at Vertex x
     * 
     * Graph g - Parameter, a graph object
     * 
     * typename Graph::VertexType x - Second parameter, a vertex of Graph g
     *   
     * map<typename Graph::VertexType> v - variable to store the list
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
}
#endif
