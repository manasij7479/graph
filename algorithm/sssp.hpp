#ifndef GRAPH_ALGORITHM_SSSP_HPP
#define GRAPH_ALGORITHM_SSSP_HPP
#include "enumeration.hpp"
#include "../structures/distance.hpp"
#include "../structures/parent.hpp"
#include "../structures/queue.hpp"
#include "../graph.hpp"
#include<limits>
#include<iostream>
namespace graph
{
    template<typename Graph>
    DistanceArray<Graph> Djikstra(Graph& g,typename Graph::VertexType s)
    {
        ParentArray<Graph> parent;
        DistanceArray<Graph> dist;
        for(auto i=g.begin();i!=g.end();++i)
            dist.set(i->first,std::numeric_limits<typename Graph::EdgeType>::max());
        dist.set(s,0);
        PriorityQueue<Graph> pq(dist);
        for(auto i=g.begin();i!=g.end();++i)
            pq.put(i->first);
        
        while(!pq.empty())
        {
            auto v=pq.get();
            for(auto i=g.nbegin(v);i!=g.nend(v);++i)
                if(pq.isElement(i->first))
                {
                    if(dist.get(i->first)>dist.get(v)+i->second)
                    {
                        dist.set(i->first,dist.get(v)+i->second);
                        parent[i->first]=v;
                    }
                }
        }
        
        return dist;
    }
}
#endif