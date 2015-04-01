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
/**	\brief sssp.hpp - Header file that has collection of single source shortest path finding algorithms.
 * 
 * The single-source shortest-paths problem refers to, given
 * a graph G , finding a shortest path from a given source vertex
 * s to every vertex x.
 * Reference Link - <a href="http://en.wikipedia.org/wiki/Shortest_path_problem#Single-source_shortest_paths">SSSP</a>
 * **/
namespace graph
{    
    using namespace std::placeholders;
    
    /**
     * \brief - Class to hold the source vertex and current state of the required datastructures
     * during a SSSP algorithm.
     * 
     * Current state includes the state of the graph, the distance array(DistanceArray<Graph>) and parent array(ParentArray<Graph>).
     * At the end of a SSSP algorithm, SSSPState contains the final state which is the return type for every
     * SSSP algprithm.
     * **/
    template <typename Graph>
    class SSSPState
    {
    public:
        typedef typename Graph::VertexType V;///<Vertex
        typedef typename Graph::EdgeType E;///<Edge
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
         * 
         * @param V u - First Parameter, source vertex
         * 
         * @param V v - Second Parameter, destination vertex
         * **/
        void relax(V u, V v)
        {
            auto w = g.weight(u,v);
            if(distance[u]<std::numeric_limits<E>::max())
				if(distance[v]>distance[u]+w)
				{
					distance[v]=distance[u]+w;
					parent[v]=u;
				}
        }
        DistanceArray<Graph>& getDistanceArray() {return distance;}///<Returns the distance array
        ParentArray<Graph>& getParentArray() {return parent;}///< Returns the parent array
        
        /** 
         * \brief - Overloaded [] operator which returns a pair of distance and parent of x
         *
         * @param V x - Parameter, a vertex
         * 
         * @returns std::pair<E,V> - pair containing distance and parent of x
         **/
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
     * \brief - Applies Djikstra's Algorithm on a grpah object
     * 
     * Djikstra's Algorithm findest the shortest path to all vertices from a single source vertex.
     * This function returns the distance array and path array after applying Djikstra's Algorithm
     * for a single source vertex
     * * Reference Link - <a href="http://en.wikipedia.org/wiki/Dijkstra's_algorithm">Dijkstra's ALgorithm</a>
     * 
     * @param Graph g - First Parameter, a graph object on which Djikstra's Algorithm is applied
     * 
     * @param typename Graph::VertexType s - Second Parameter, a vertex of graph g and the source
     * 								  for Djikstra's algorithm
     * 
     * @returns SSSPState<Graph> state - Contains the modified parent array and distance array after applying Djikstra's Algorithm
     * **/
    template<typename Graph>
    SSSPState<Graph> Djikstra(Graph& g,typename Graph::VertexType s)
    {
        typedef typename Graph::VertexType V;
        SSSPState<Graph> state(g,s);
        ParentArray<Graph>& parent=state.getParentArray();
        DistanceArray<Graph>& dist=state.getDistanceArray();
        
        PriorityQueue<Graph> pq([&](V x,V y){return dist[x]<dist[y];},VertexList(g));
        
        while(!pq.empty())
        {
            auto u=pq.get();
            VisitNeighbours(g,u,[&state,&u](V v){state.relax(u,v);});
        }
        
        return state;
    }
    /**
     * \brief - Applies Bellman-Ford Algorithm on a graph object
     * 
     * Bellman-Ford Algorithm findest the shortest path to all vertices from a single source vertex.
     * This function returns the distance array and path array after applying Bellman-Ford Algorithm
     * for a single source vertex.
     * * Reference Link - <a href="http://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm">Bellman-Ford Algorithm</a>
     * 
     * @param Graph g - First Parameter, a graph object on which Djikstra's Algorithm is applied
     * 
     * @param typename Graph::VertexType s - Second Parameter, a vertex of graph g and the source
     * 								  for Djikstra's algorithm
     * 
     * @returns SSSPState<Graph> state - Contains the modified parent array and distance array after applying Bellman-Ford Algorithm
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
