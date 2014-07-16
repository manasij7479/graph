#ifndef GRAPH_ALGORITHM_COLLECTIONS_HPP
#define GRAPH_ALGORITHM_COLLECTIONS_HPP
#include "../graph.hpp"
#include "../search/bfs.hpp"
#include "enumeration.hpp"
#include<vector>
#include<map>
#include<tuple>
#include<algorithm>
namespace graph
{
    template<typename Graph>
    std::vector<typename Graph::VertexType> vertices(Graph& g)
    {
        std::vector<typename Graph::VertexType> v;
        for(auto i=g.begin();i!=g.end();++i)
            v.push_back(i->first);
        return v;
    }
    
    template<typename Graph>
    std::vector<std::tuple<typename Graph::VertexType,typename Graph::VertexType,typename Graph::EdgeType>> edges(Graph& g,bool duplicate)
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
}
#endif