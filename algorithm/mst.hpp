#ifndef GRAPH_ALGORITHM_MST_HPP
#define GRAPH_ALGORITHM_MST_HPP
#include "../graph.hpp"
#include "collections.hpp"
#include "../util/visitors.hpp"
#include "enumeration.hpp"
#include "../structures/disjointset.hpp"
#include "../structures/queue.hpp"
#include<map>
#include<list>
#include<vector>
#include<tuple>
#include<algorithm>
#include<limits>
/**
 * \brief mst.hpp - Header file that contains collectin of all Minimum Cost Spanning Tree finding algorithms
 * 
 * A spanning tree is a subgraph of a graph, which is a tree and connects all the vertices
 * of the graph. A Minimum Cost Spanning Tree is a spanning tree with cost or weight less 
 * than all other spanning trees. There might be multiple Minimum Cost Spanning Trees for
 * a graph. Each algorithm might return different Minimum Cost Spanning Tree.
 * Reference Lin - <a href="http://en.wikipedia.org/wiki/Minimum_spanning_tree">MST</a>
 * **/
namespace graph
{
    /**
     * \brief - Class to hold the current state of the required datastructures
     * during a MST computing algorithm.
     * 
     * Current state includes the state of the graph, the MST and the span of the MST..
     * At the end of a MST computing algorithm, MSTState contains the final state which is the return type for every
     * MST computing algorithm.
     * **/
    template<typename Graph>
    class MSTState
    {
    public:
        typedef typename Graph::VertexType V;///<Vertex
        typedef typename Graph::EdgeType E;///<Edge
        /**
         * \brief - Constructor to initialize the graph with all the vetices but no edges
         * **/
        MSTState(Graph g)
        {
            for(auto i=g.begin();i!=g.end();++i)
                mst.insertVertex(i->first);
            span=0;
        }
        
        Graph& getMst() { return mst;}///< Returns the MST
        E getSpan() {return span;}///<Returns the span of MST
        /**
         * \brief - Function to insert edges into the graph while creating Minimum Cost Spanning Tree
         * 
         * @param V x - First Parameter, a vertex
         * 
         * @param V y - Second Paramete, a vertex
         * 
         * @param E w - Third Parameter, edge weight between x and y
         * **/
        void insertEdge(V x,V y,E w) 
        { 
            mst.insertEdge(x,y,w);
            span += w;
        }
        int order() { return mst.order();}///<Returns the order of MST
        //int size() { return Size(mst);}
        
    private:
        Graph mst;
        E span;
    };
    /**
     * \brief - Returns the Minimum Cost Spanning tree obtained using Kruskal's ALgorithm
     * 
     * Reference Link - <a href="http://en.wikipedia.org/wiki/Kruskal%27s_algorithm">Kruskal's ALgorithm</a>
     * 
     * @param Graph g - First Parameter, a graph on which Kruskal's Algorithm is implemented
     * 
     * @param F callback - Second Parameter, a hook to facilitate different functions
     * 
     * @returns MSTState<Graph> state - holds the Minimum Cost Spanning tree after Kruskal's Algorithm is applied
     * **/
    template<typename Graph, typename F>
    MSTState<Graph> Kruskal(Graph g, F callback)
    {
        MSTState<Graph> state(g); 
        auto e = sortedEdgeList(g,false);
        DisjointSet<Graph> ds(g);
        
        int size=0;
        for(uint i=0;i<e.size();++i)
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
    
    /**
     * \brief - Returns the Minimum Cost Spanning tree obtained using Boruvka ALgorithm
     * 
     * Reference Link - <a href="http://en.wikipedia.org/wiki/Bor%C5%AFvka%27s_algorithm">Boruvka's ALgorithm</a>
     * 
     * @param Graph g - Parameter, a graph on which Boruvka Algorithm is implemented
     * 
     * @returns MSTState<Graph> state - holds the Minimum Cost Spanning tree after Boruvka Algorithm is applied
     * **/
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
    
    /**
     * \brief - Returns the Minimum Cost Spanning tree obtained using Prim's ALgorithm
     * 
     * Reference Link - <a href="http://en.wikipedia.org/wiki/Prim%27s_algorithm">Prim's ALgorithm</a>
     * 
     * @param Graph g - Parameter, a graph on which Boruvka Algorithm is implemented
     * 
     * @returns MSTState<Graph> state - holds the Minimum Cost Spanning tree after Prim's Algorithm is applied
     * **/
    
    template<typename Graph>
    MSTState<Graph> Prim (Graph& g)
    {
        typedef typename Graph::VertexType V;
        typedef typename Graph::EdgeType E;
        std::vector <V> v_new=VertexList(g);
        MSTState<Graph> state(g);
        std::map<V,V> parent;
        std::map<V,E> cost;
        
        for(auto i=g.begin();i!=g.end();++i)
            cost[i->first]=std::numeric_limits<E>::max();
        cost[g.begin()->first]=0;
        
        PriorityQueue<Graph> pq([&](V x,V y){return cost[x]<cost[y];},v_new);
        
        while(!pq.empty())
        {
            auto u=pq.get();
            for(auto i=g.nbegin(u);i!=g.nend(u);++i)
            {
                if((g.weight(i->first,u)<cost[i->first])&&pq.isElement(i->first))
                {
                    parent[i->first]=u;
                    cost[i->first]=g.weight(i->first,u);
                }
            }
            pq.heapify();
        }
        
        for(auto i=parent.begin();i!=parent.end();++i)                   //creating tree from parent array
        {
            state.insertEdge(i->first,i->second, g.weight(i->first,i->second));
        }
        
        return state;
    }
}

#endif
