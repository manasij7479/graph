#ifndef GRAPH_ALGORITHM_SSSP_HPP
#define GRAPH_ALGORITHM_SSSP_HPP
#include "enumeration.hpp"
#include "collections.hpp"
#include "../structures/distance.hpp"
#include "../structures/parent.hpp"
#include "../structures/queue.hpp"
#include "../graph.hpp"
#include "../util/visitors.hpp"
#include <limits>
namespace graph
{    
    using namespace std::placeholders;
    
    template <typename Graph>
    class SSSPState
    {
    public:
        typedef typename Graph::VertexType V;
        typedef typename Graph::EdgeType E;
        SSSPState(Graph& g_,V s):g(g_),source(s)
        {
            for(auto i=g.begin();i!=g.end();++i)
                distance.set(i->first,std::numeric_limits<E>::max());
            distance.set(source,0);
            parent[source]=source;
        }
        void relax(V u, V v)
        {
            auto w = g.weight(u,v);
            if(distance[v]>distance[u]+w)
            {
                distance[v]=distance[u]+w;
                parent[v]=u;
            }
        }
        DistanceArray<Graph>& getDistanceArray() {return distance;}
        ParentArray<Graph>& getParentArray() {return parent;}
        
        std::pair<E,V> operator[](V x)
        {
            return std::make_pair(distance[x],parent[x]);
        }
        
    private:
        Graph& g;
        typename Graph::VertexType source;
        ParentArray<Graph> parent;
        DistanceArray<Graph> distance;
    };
    
    template<typename Graph>
    SSSPState<Graph> Djikstra(Graph& g,typename Graph::VertexType s)
    {
        typedef typename Graph::VertexType V;
        SSSPState<Graph> state(g,s);
        ParentArray<Graph>& parent=state.getParentArray();
        DistanceArray<Graph>& dist=state.getDistanceArray();
        
        PriorityQueue<Graph> pq([&](V x,V y){return dist[x]<dist[y];});
        for(auto i=g.begin();i!=g.end();++i)
            pq.put(i->first);
        
        while(!pq.empty())
        {
            auto u=pq.get();
            VisitNeighbours(g,u,[&state,&u](V v){state.relax(u,v);});
        }
        
        return state;
    }
    
    //FIXME: Assumes no negative cycle, may segfault
    //put proper checks later
    template<typename Graph>
    SSSPState<Graph> BellmanFord(Graph& g,typename Graph::VertexType s)
    {
        typedef typename Graph::VertexType V;
        SSSPState<Graph> state(g,s);
        for (int i=1; i< g.order()-1; ++i)
        {
            VisitEdges(g,std::bind(&SSSPState<Graph>::relax, &state, _1,_2));
        }
        return state;
    }
    
}
#endif