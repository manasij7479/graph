#ifndef GRAPH_ALGORITHM_ENUMERATION_HPP
#define GRAPH_ALGORITHM_ENUMERATION_HPP    
#include "../graph.hpp"
#include "collections.hpp"
namespace graph
{
    template<typename Graph>
    int Size(Graph& g)
    {
        return EdgeList(g,false).size();
    }
    
    template<typename Graph>
    int outDegree(Graph& g, typename Graph::VertexType v)
    {
        int count=0;
        for(auto i=g.nbegin(v);i!=g.nend(v);++i)
            count++;
        return count;
    }
    
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
    
    template<typename Graph>
    int degree(Graph& g,typename Graph::VertexType v)
    {
        if(!g.isDirected())
            return outDegree(g,v);
        else
            return inDegree(g,v)+outDegree(g,v);
    }
    
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
    
    template<typename Graph>
    float Density(Graph& g)
    {
        return (2.0*Size(g))/(g.order()*(g.order()-1));
    }
}
#endif
