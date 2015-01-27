/**	\brief sssp.hpp - Header file that has collection of single source shortest path finding algorithms
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
        APSPState(Graph& g_):g(g_)
        {
            for(auto i=g.begin();i!=g.end();++i)
            {	
                for (auto j=g.begin();j!=g.end();++j)					
                {	
                    if(i->first==j->first)
                        distance [std::make_pair(i->first,j->first)]=0;
                    else if (!(isAdjacent(g, i->first, j->first)))
                        distance [std::make_pair(i->first,j->first)]=std::numeric_limits<E>::max();
                    else if(i->first!=j->first)
                    {
                        distance [std::make_pair(i->first,j->first)]=g.weight(i->first,j->first);
                        next[std::make_pair(i->first,j->first)] = j->first;
                    }
                    
                }
            }
        }
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
                    //std::cout<<u<<" "<<v<<" ->";
                    if(next.find(std::make_pair(u,v)) == next.end())
                        continue;
                    x=u;
                    path[std::make_pair(u,v)].push_back(u);
                    while (x != v)
                    {
                        //std::cout<<u<<"->";
                        x=next[std::make_pair(x,v)];
                        //std::cout<<u<<" ";
                        path[std::make_pair(u,v)].push_back(x);
                    }
                    //std::cout<<std::endl;
                }
            }
            return path;
        }
        
    private:
        Graph& g;
        NM next;
        AM distance;
    };
    
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

