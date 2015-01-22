#ifndef GRAPH_STRUCTURES_DISJOINTSET_HPP
#define GRAPH_STRUCTURES_DISJOINTSET_HPP
#include "parent.hpp"
#include <map>
namespace graph
{
    template<typename Graph>
    class DisjointSet
    {
    public:
        typedef typename Graph::VertexType V;
        
        DisjointSet(Graph g)
        {
            for(auto i=g.begin();i!=g.end();++i)
            {
                parent[i->first] = i->first;
                rank[i->first] = 0;
            }
        }
        
        V findRoot(V v)
        {
            if(v != parent[v])
                return findRoot(parent[v]);
            else
                return v;
        }
        
        bool Union(V x,V y)
        {
            V xroot = findRoot(x);
            V yroot = findRoot(y);
            if(xroot == yroot)
                return false;

            if(rank[xroot] < rank[yroot])
                parent[xroot]=yroot;
            else if(rank[xroot] > rank[yroot])
                parent[yroot]=xroot;
            else
            {
                parent[yroot]=xroot;
                rank[xroot]++;
            }
            return true;
        }
        
    private:
        std::map<V,int> rank;
        ParentArray<Graph> parent;
    };
    
}
#endif