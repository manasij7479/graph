#ifndef GRAPH_SEARCH_HPP
#define GRAPH_SEARCH_HPP
#include "../graph.hpp"
#include "../implementation/edge_traits.hpp"
#include <map>
#include <vector>
namespace graph
{
    template
    <
        typename Graph,
        template <typename> class Container
    >
    class Search
    {
    public:
        typedef typename Graph::VertexType VertexType;
        typedef typename Graph::EdgeType EdgeType;
        typedef typename edge_traits<EdgeType>::DistanceType DistanceType;
        
        Search(Graph& g_,const VertexType& s)
            :fringe(dist),g(g_),source(s)
        {
            dist[source]=DistanceType(0);
            parent[source]=source;
            fringe.put(source);
            
            while(!fringe.empty())
            {
                VertexType v=fringe.get();
                for(auto y=g.nbegin(v);y!=g.nend(v);++y)
                {
                    if(dist.find(y->first)==dist.end())
                    {
                        dist[y->first]=dist[v]+y->second;
                        fringe.put(y->first);
                        parent[y->first]=v;
                    }
                }
            }
            
            
        }
        DistanceType distanceTo(const VertexType& v)
        {
            return dist[v];
        }
        std::vector<VertexType> getPath(const VertexType& v)
        {
                std::vector<VertexType> result;
                VertexType temp=v;
                while(parent[temp]!=temp)
                {
                    result.push_back(temp);
                    temp=parent[temp];
                }
                result.push_back(temp);
                std::reverse(result.begin(),result.end());
                return result;
        }
    private:
        Container<Graph> fringe;
        std::map<VertexType,DistanceType> dist;
        std::map<VertexType,VertexType> parent;
        Graph& g;
        VertexType source;
    };
}
#endif