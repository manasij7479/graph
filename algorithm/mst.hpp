#ifndef GRAPH_ALGORITHM_MST_HPP
#define GRAPH_ALGORITHM_MST_HPP
#include "../graph.hpp"
#include "collections.hpp"
#include "enumeration.hpp"
#include "../structures/disjointset.hpp"
#include<map>
#include<list>
#include<vector>
#include<tuple>
#include<algorithm>
#include<limits>
namespace graph
{
    template<typename Graph>
    class MSTState
    {
    public:
        typedef typename Graph::VertexType V;
        typedef typename Graph::EdgeType E;
        
        MSTState(Graph g)
        {
            for(auto i=g.begin();i!=g.end();++i)
                mst.insertVertex(i->first);
            span=0;
        }
        
        Graph& getMst() { return mst;}
        E getSpan() {return span;}
        
        void insertEdge(V x,V y,E w) 
        { 
            mst.insertEdge(x,y,w);
            span += w;
        }
        int order() { return mst.order();}
        //int size() { return Size(mst);}
        
    private:
        Graph mst;
        E span;
    };
    
    template<typename Graph, typename F>
    MSTState<Graph> Kruskal(Graph g, F callback)
    {
        MSTState<Graph> state(g); 
        auto e = sortedEdgeList(g,false);
        DisjointSet<Graph> ds(g);
        
        int size=0;
        for(int i=0;i<e.size();++i)
        {
            if(size == state.order()-1)
                break;
            auto x = std::get<0>(e[i]);
            auto y = std::get<1>(e[i]);
            auto w = std::get<2>(e[i]);
            if(ds.Union(x,y) == true)
            {
                state.insertEdge(x,y,w);
                callback(x,y,w);
                size++;
            }
        }
        return state;
    }
    
    template <typename Graph>
    MSTState<Graph> Boruvka(Graph g)
    {
        typedef typename Graph::VertexType V;
        typedef typename Graph::EdgeType E;
        MSTState<Graph> state(g);
        DisjointSet<Graph> ds(g);
        std::map<V, std::tuple<V,V,E>> compMinEdge;
        
        int size=0;
        while(size < state.order()-1)
        {
            for(auto i=g.begin();i!=g.end();++i)                                   //finding edge with min weight leaving from every vertex
            {
                E min = std::numeric_limits<E>::max();
                V x;
                for(auto j=g.nbegin(i->first);j!=g.nend(i->first);++j)
                {
                    if(j->second < min && !isAdjacent(state.getMst(),i->first,j->first))
                    {
                        min = j->second;
                        x = j->first;
                    }
                }
                auto root = ds.findRoot(i->first);
                if(compMinEdge.find(root) == compMinEdge.end())                     //finding edge with min weight of every component
                    compMinEdge[root] = std::make_tuple(i->first,x,min);
                else if(std::get<2>(compMinEdge[root]) > min)
                    compMinEdge[root] = std::make_tuple(i->first,x,min);
            }
            for(auto it=compMinEdge.begin();it!=compMinEdge.end();++it)            //inserting edge with min weight of every component to mst
            {
                if(ds.Union(std::get<0>(it->second), std::get<1>(it->second)))
                {
                    state.insertEdge(std::get<0>(it->second), std::get<1>(it->second), std::get<2>(it->second));
                    size++;
                }
            }
            compMinEdge.clear();
        }
        
        return state;
    }
}

#endif