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
        
        Graph getMst() { return mst;}
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
    
    template<typename Graph>
    MSTState<Graph> Kruskal(Graph g)
    {
        MSTState<Graph> state(g); 
        auto e = sortedEdgeList(g,false);
        DisjointSet<Graph> ds(g);
        
        int size=0;
        for(int i=0;i<e.size();++i)
        {
            if(size == state.order())
                break;
            auto x = std::get<0>(e[i]);
            auto y = std::get<1>(e[i]);
            auto w = std::get<2>(e[i]);
            if(ds.Union(x,y) == true)
            {
                state.insertEdge(x,y,w);
                size++;
            }
        }
        return state;
    }
}

#endif