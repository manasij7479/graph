#ifndef GRAPH_ALGORITHM_COLLECTIONS_HPP
#define GRAPH_ALGORITHM_COLLECTIONS_HPP
#include "../graph.hpp"
#include "../search/bfs.hpp"
#include "../search/ucs.hpp"
#include "enumeration.hpp"
#include "predicates.hpp"
#include<vector>
#include<map>
#include<set>
#include<tuple>
#include<algorithm>
#include<stdexcept>
namespace graph
{
    template<typename Graph>
    std::vector<typename Graph::VertexType> VertexList(Graph& g)
    {
        std::vector<typename Graph::VertexType> v;
        for(auto i=g.begin();i!=g.end();++i)
            v.push_back(i->first);
        return v;
    }
    
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
    
    template<typename Graph>
    std::map<typename Graph::VertexType,int> DegreeList(Graph& g)
    {
        std::map<typename Graph::VertexType,int> m;
        for(auto i=g.begin();i!=g.end();++i)
            m[i->first]=degree(g,i->first);
        return m;
    }
    
    template<typename Graph>
    std::vector<int> DegreeSequence(Graph& g)
    {
        std::vector<int> ds;
        for(auto i=g.begin();i!=g.end();++i)
            ds.push_back(degree(g,i->first));
        std::sort(ds.begin(),ds.end());
        return ds;
    }
    
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
            auto d=ucs.getDistArray();
            auto max=d.begin()->second;
            for(auto j=d.begin();j!=d.end();++j)
                if(j->second>max)
                    max=j->second;
             m[i->first]=max;
        }
        return m;
    }
    
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
    
}
#endif