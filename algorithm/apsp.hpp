#ifndef GRAPH_ALGORITHM_APSP_HPP
#define GRAPH_ALGORITHM_APSP_HPP
#include "enumeration.hpp"
#include "collections.hpp"
#include "predicates.hpp"
#include "../structures/distance.hpp"
#include "../structures/parent.hpp"
#include "../structures/queue.hpp"
#include "../graph.hpp"
#include "../util/visitors.hpp"
#include <limits>
/**	\brief apsp.hpp - Header file that has collection of all pair shortest path finding algorithms
 * 
 * The All-Pairs Shortest Path problem finds the shortest paths between every pair of vertices v, v' in the graph.
 * Reference Link - <a href="http://en.wikipedia.org/wiki/Shortest_path_problem#All-pairs_shortest_paths">APSP</a>
 * **/
namespace graph
{    
    //     using namespace std::placeholders;
    
    /**
     * \brief - Class to hold the current state of the required datastructures during an APSP algorithm.
     * 
     * Current state includes the state of the graph, the distance matrix and the path matrix.
     * At the end of an APSP algorithm, APSPState contains the final state which is the return type for every
     * APSP algprithm.
     * **/
    template <typename Graph>
    class APSPState
    {
    public:
        typedef typename Graph::VertexType V;///<Vertex
        typedef typename Graph::EdgeType E;///<Edge
        typedef typename edge_traits<E>::DistanceType D;///<Distance
        typedef typename std::map<std::pair<typename Graph::VertexType,typename Graph::VertexType>, std::vector<typename Graph::VertexType>> PM; ///< Path Matrix
        typedef typename std::map<std::pair<typename Graph::VertexType,typename Graph::VertexType>,D> AM; ///<Adjacency Matrix
        typedef typename std::map<std::pair<typename Graph::VertexType,typename Graph::VertexType>, typename Graph::VertexType> NM;///<Next Matrix
        /**
         * \brief - Constructor to initialize the distance matrix and path matrix
         * **/
        APSPState(Graph& g_):g(g_)
        {
            for(auto i=g.begin();i!=g.end();++i)
            {	
                for (auto j=g.begin();j!=g.end();++j)					
                {	
                    if(i->first==j->first)
                        distance [std::make_pair(i->first,j->first)]=0;
                    else if (!(isAdjacent(g, i->first, j->first)))
                        distance [std::make_pair(i->first,j->first)]=std::numeric_limits<D>::max();
                    else if(i->first!=j->first)
                    {
                        distance [std::make_pair(i->first,j->first)]=g.weight(i->first,j->first);
                        next[std::make_pair(i->first,j->first)] = j->first;
                    }
                    
                }
            }
        }
        /**
         * \brief - Function to determine the shortest path between a pair of vertices
         * 
         * This function finds the shortest path between a pair of vetices 'i' and
         * 'j' through a vertex 'k' and updates the distance and the shortest path 
         * accordingly.
         * 
         * @param V k - First parameter, a vertex
         * 
         * @param V i - Second parameter, source vertex
         * 
         * @param V j - Third parameter, destination vertex
         * **/
        void relax(V k, V i, V j)
        {
            if(distance[std::make_pair(i,k)]<std::numeric_limits<E>::max() && distance[std::make_pair(k,j)]<std::numeric_limits<E>::max())
                if (distance[std::make_pair(i,j)] > distance[std::make_pair(i,k)] + distance[std::make_pair(k,j)])
                {
                    distance[std::make_pair(i,j)] = distance[std::make_pair(i,k)] + distance[std::make_pair(k,j)];
                    next[std::make_pair(i,j)]=next[std::make_pair(i,k)];
                }
        }
        
        /**
         * \brief - returns Adjacency Matrix
         * 
         * @returns AM distance - an Adjancency matrix
         * **/
        
        AM getDistanceArray() {return distance;}
        /**
         * \brief - Function to determine an initial path between all pairs of vertices of a graph
         * 
         * @returns PM path - a path matrix
         * **/
        PM getPathArray()
        {
            PM path;
            
            for(auto i=g.begin();i!=g.end();++i)
            {
                for (auto j=g.begin();j!=g.end();++j)
                {
                    V u = i->first;
                    V v = j->first;
                    V x;
                    if(next.find(std::make_pair(u,v)) == next.end())
                        continue;
                    x=u;
                    path[std::make_pair(u,v)].push_back(u);
                    while (x != v)
                    {
                        x=next[std::make_pair(x,v)];
                        path[std::make_pair(u,v)].push_back(x);
                    }
                }
            }
            return path;
        }
        
    private:
        Graph& g;
        NM next;
        AM distance;
    };
    /**
     * \brief - Function to implement Floyd-Roy-Warshall Algorithm
     * 
     * Returns the path matrix and distance matrix of a graph after applying
     * Floyd-Roy-Warshall Algorithm. This algorithm finds the shortest path possible
     * between all pairs of vertices. It returns both the shortest path and the shortest 
     * distance between all pairs of vertices.
     * Reference Lin  - <a href="http://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm">FLoyd-Roy-Warshall ALgorithm</a>
     * 
     * @param Graph g - Parameter, a graph object on which Floyd-Roy-Warshall Algorithm is applied
     * 
     * @returns APSPState<Graph> state - Contains the modified path matrix and distance matrix after applying Floyd-Roy-Warshall Algorithm
     * **/
    template<typename Graph>
    APSPState<Graph> FloydRoyWarshall(Graph& g)
    {
        typedef typename std::map<std::pair<typename Graph::VertexType,typename Graph::VertexType>,typename Graph::EdgeType> AM;
        APSPState<Graph> state(g);
        
        for (auto k=g.begin();k!=g.end();++k) 
            for(auto i=g.begin();i!=g.end();++i)
                for (auto j=g.begin();j!=g.end();++j)	
                    state.relax(k->first, i->first, j->first);
        return state;
    }
    
    
}
#endif

