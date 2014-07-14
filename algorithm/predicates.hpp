#ifndef GRAPH_ALGORITHM_PREDICATES_HPP
#define GRAPH_ALGORITHM_PREDICATES_HPP
#include "../graph.hpp"
# include "../algorithm/enumeration.hpp"
#include "../search/search.hpp"
#include "../search/dfs.hpp"
#include<vector>
#include<algorithm>
namespace graph
{
    template<typename Graph>
    bool isVertex(Graph& g,typename Graph::VertexType x)
    {
        return g.find(x)!=g.end();
    }
    
    template<typename Graph>
    bool isAdjacent(Graph& g,typename Graph::VertexType x,typename Graph::VertexType y)
    {
        if(isVertex(g,x) && isVertex(g,y))
            return g.nfind(x,y)!=g.nend(x);
        return false;
    }
    
    template<typename Graph>
    bool isSubgraph(Graph& g,Graph& h)
    {
        if(h.order()>g.order())
            return false;
        std::vector<typename Graph::VertexType> v;
        for(auto x=g.begin();x!=g.end();++x)
            v.push_back(x->first);
        for(auto x=h.begin();x!=h.end();++x)
        {
            if(std::find(v.begin(),v.end(),x->first)==v.end())
                return false;
            else
            {
                std::vector<typename Graph::VertexType> e;
                for(auto y=g.nbegin(x->first);y!=g.nend(x->first);++y)
                    e.push_back(y->first);
                for(auto y=h.nbegin(x->first);y!=h.nend(x->first);++y)
                    if(std::find(e.begin(),e.end(),y->first)==e.end())
                        return false;
            }
        }
        return true;
    }
    
    template<typename Graph>
    bool isSpanningSubgraph(Graph& g,Graph& h)
    {
        if(g.order()==h.order() && isSubgraph(g,h))
            return true;
        return false;
    }
    template<typename Graph>
    bool isConnected(Graph& g)
    {
        //pore change korte hobe TODO
        return true;
    }
    template <typename Graph>
    bool isRegular(Graph &g)
    {
        int k=degree(g,g.begin()->first);
        for (auto x=g.begin();x!=g.end();x++)
            if(k!=degree(g,x->first))
                return false;
            return true;
    }
    template <typename Graph>
    bool isEulerian(Graph &g)
    {
        if (isConnected(g))
        {	for (auto x=g.begin();x!=g.end();x++)
            {
                int k=degree(g,x->first);
                if(k%2!=0)
                    return false;
            }
            return true;
        }
        else
            return false;
    }
    template <typename Graph>
    bool isSemiEulerian(Graph &g)
    {
        if (isConnected(g))
        {	int count=0;
            for (auto x=g.begin();x!=g.end();x++)
            {
                int k=degree(g,x->first);
                if(k%2!=0)
                    count++;
            }
            if(count==2)
                return true;
            else
                return false;
        }
        else
            return false;
    }
    template <typename Graph>
    bool isComplete(Graph &g)
    {
        for (auto x=g.begin();x!=g.end();x++)
            for (auto y=g.begin();y!=g.end();y++)
                if (x!=y && !(isAdjacent(g,x->first,y->first)))
                    return false;
                
                return true;
    }
    template <typename Graph>
    bool isComplement(Graph &g, Graph &h)
    {
        for (auto x=g.begin();x!=g.end();x++)
            for (auto y=g.begin();y!=g.end();y++)
                if (x!=y)
                    if(isAdjacent(g,x->first,y->first) && isAdjacent(h,x->first,y->first))
                        return false;
                    
                    return true;
    }
    template <typename Graph>
    bool isEdgeless(Graph &g)
    {
        for (auto x=g.begin();x!=g.end();x++)
            for (auto y=g.begin();y!=g.end();y++)
                if(isAdjacent(g,x->first,y->first))
                    return false;
                
                return true;

    }
    
    template<typename Graph>
    bool isCyclic(Graph& g)
    {
        HookedSearch<Graph,Stack> searchObject(g,g.begin()->first);
        bool cyclic=false;
        searchObject.m_p3=[&](const typename Graph::VertexType& v)
        {
            cyclic=true;
            return false;
        };
        searchObject.execute();
        return cyclic;
    }
    template<typename Graph>
    bool isEmpty(Graph& g)
    {
       return (g.begin()==g.end());
    }
}
#endif
