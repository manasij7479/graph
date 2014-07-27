#ifndef GRAPH_ALGORITHM_PREDICATES_HPP
#define GRAPH_ALGORITHM_PREDICATES_HPP
#include "../graph.hpp"
# include "enumeration.hpp"
#include "../search/bfs.hpp"
#include "../search/dfs.hpp"
#include "collections.hpp"
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
    bool isSubgraph(Graph& g,Graph& h) //is 'g' subgraph of 'h'
    {
        if(h.order()<g.order())
            return false;
        for(auto i=g.begin();i!=g.end();++i)
            if(!(isVertex(h,i->first)))
                return false;
        for(auto i=g.begin();i!=g.end();++i)
            for(auto j=g.nbegin(i->first);j!=g.nend(i->first);++j)
                if(!(isAdjacent(h,i->first,j->first)))
                    return false;
        return true;
    }
    
    template<typename Graph>
    bool isSpanningSubgraph(Graph& g,Graph& h) //is 'g' spanning_subgraph of 'h'
    {
        if(g.order()==h.order() && isSubgraph(g,h))
            return true;
        return false;
    }
    
    template<typename Graph>
    bool isConnected(Graph& g)
    {
        BreadthFirstSearch<Graph> bfs(g,g.begin()->first);
        bfs();
        auto d=bfs.getDistArray();
        
        return d.size()==g.order();
    }
    
    template<typename Graph>
    bool isConnected(Graph& g,typename Graph::VertexType x,typename Graph::VertexType y)
    {
        HookedSearch<Graph,Queue> searchObject(g,x);
        bool connected=false;
        searchObject.m_p2=[&](const typename Graph::VertexType& v)
        {
            if(v==y)
            {
                connected=true;
                return false;
            }
            return true;
        };
        searchObject.execute();
        return connected;
    }
    
    template<typename Graph>
    bool isComponent(Graph& g1,Graph& g2)  //is 'g1' component of 'g2' 
    {
        if(!(isConnected(g1)&&isSubgraph(g1,g2)))
            return false;
        BreadthFirstSearch<Graph> bfs(g2,g1.begin()->first);
        bfs();
        auto d=bfs.getDistArray();
        if(d.size()!=g1.order())
            return false;
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
    bool isCentre(Graph& g,typename Graph::VertexType x)
    {
        auto s=Centre(g);
        return s.find(x)!=s.end();
    }
    
    template<typename Graph>
    bool isPeriphery(Graph& g,typename Graph::VertexType x)
    {
        auto s=Periphery(g);
        return s.find(x)!=s.end();
    }
    
    template<typename Graph>
    bool isEmpty(Graph& g) //is vertexless graph
    {
       return (g.begin()==g.end());
    }
}
#endif
