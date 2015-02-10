/**	\brief sssp.hpp - Header file that has collection of single source shortest path finding algorithms
 * **/

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
        /**
         * \brief - Constructor to initialize distance array and parent array
         * **/
        SSSPState(Graph& g_,V s):g(g_),source(s)
        {
            for(auto i=g.begin();i!=g.end();++i)
                distance.set(i->first,std::numeric_limits<E>::max());
            distance.set(source,0);
            parent[source]=source;
        }
        /**
         * \brief - Function to calculate shortest path between two vertices 'u' and 'v'
         * **/
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
    /**
     * \brief - Returns the parent array and distance array of a graph after applying
     * 			Djikstra's Algorithm
     * 
     * Graph g - First Parameter, a graph object on which Djikstra's Algorithm is applied
     * 
     * typename Graph::VertexType s - Second Parameter, a vertex of graph g and the source
     * 								  for Djikstra's algorithm
     * 
     * SSSPState<Graph> state - Contains the modified parent array and distance array after applying Djikstra's Algorithm
     * **/
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
    /**
     * \brief - Returns the parent array and distance array of a graph after applying
     * 			Bellman-Ford Algorithm
     * 
     * Graph g - First Parameter, a graph object on which Djikstra's Algorithm is applied
     * 
     * typename Graph::VertexType s - Second Parameter, a vertex of graph g and the source
     * 								  for Djikstra's algorithm
     * 
     * SSSPState<Graph> state - Contains the modified parent array and distance array after applying Bellman-Ford Algorithm
     * **/
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
