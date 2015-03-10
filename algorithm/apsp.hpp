/**	\brief apsp.hpp - Header file that has collection of all pair shortest path finding algorithms
 * **/

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
namespace graph
{    
    //     using namespace std::placeholders;
    
    template <typename Graph>
    class APSPState
    {
    public:
        typedef typename Graph::VertexType V;
        typedef typename Graph::EdgeType E;
        typedef typename edge_traits<E>::DistanceType D;
        typedef typename std::map<std::pair<typename Graph::VertexType,typename Graph::VertexType>, std::vector<typename Graph::VertexType>> PM;
        typedef typename std::map<std::pair<typename Graph::VertexType,typename Graph::VertexType>,D> AM;
        typedef typename std::map<std::pair<typename Graph::VertexType,typename Graph::VertexType>, typename Graph::VertexType> NM;
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
         * \brief - Function to determine the shortest path between a pair of vertices 'i' and
         * 			'j' through a vertex 'k'
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
        AM getDistanceArray() {return distance;}
        /**
         * \brief - Function to determine an initial path between all pairs of vertices of a graph
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
     * \brief - Returns the path matrix and distance matrix of a graph after applying
     * 			Floyd-Roy-Warshall Algorithm
     * 
     * Graph g - Parameter, a graph object on which Floyd-Roy-Warshall Algorithm is applied
     * 
     * APSPState<Graph> state - Contains the modified path matrix and distance matrix after applying Floyd-Roy-Warshall Algorithm
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
