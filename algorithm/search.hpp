#ifndef GRAPH_SEARCH_HPP
#define GRAPH_SEARCH_HPP
#include "../graph.hpp"
#include "../implementation/edge_traits.hpp"
#include "../structures/stack.hpp"
#include "../structures/queue.hpp"
#include "../structures/parent.hpp"
#include <map>
#include <vector>
#include <functional>
/** \brief seacrh.hpp - Contains execution of different searching algorithms with and without using Callback Funtions.
 * 
 * In computer science, graph search is the problem of visiting all the nodes in a graph in a particular
 * manner, updating and/or checking their values along the way.
 * Refernce Link  - <a href="http://en.wikipedia.org/wiki/Graph_traversal">Graph Search</a>
 * **/

namespace graph
{
     /**
     * \brief - The basic framework to implement Graph Search
     * 
     * Container<Graph> fringe - can be used as a stack, queue or priority queue in this context
     * **/   
    template
    <
        typename Graph,
        template <typename> class Container
    >
    class Search
    {
    public:
        typedef typename Graph::VertexType V;///<Vertex
        typedef typename Graph::EdgeType E;///<Edge
        typedef typename edge_traits<E>::DistanceType D;///<Distance
        /**
         * \brief - Constructor to initialize the graph, the source vertex as per input
         * 
         * Initialize fringe with the template variable Container and initializing
         * the hooks with true value.
         * **/
        Search
        (
            Graph& g_,
            const V& s
        )
        :g(g_),source(s) 
        {
            fringe = new Container<Graph>([this](V x,V y){return this->dist[x] < this->dist[y];});
            p1=p2=p3=
            [](const V&)
            {
                return true;
            };
            p4=[](const V&,const V&)
            {
                return true;
            };
        }
        /**
         * \brief - Destructor
         * **/
        virtual ~Search(){}
        /**
         * \brief - overloaded () operator which performs the search 
         **/
        virtual void operator()()
        {
            dist[source]=D(0);
            parent[source]=source;
            fringe->put(source);
            if(!p1(source))
                return;
            while(!fringe->empty())
            {
                V v=fringe->get();
                if(!p2(v))
                    return;
                for(auto y=g.nbegin(v);y!=g.nend(v);++y)
                {
                    
                    if(dist.isUnknown(y->first))
                    {
                        dist.set(y->first,dist[v]+y->second);
                        fringe->put(y->first);
                        parent[y->first]=v;
                        if(!p4(v,y->first))
                            return;
                    }
                    else
                    {
                        //back edge
                        if(g.isDirected())
                        {
                            if(!p3(y->first))
                                return;
                        }
                        else
                        {
                            if(parent[v]!=y->first)
                                if(!p3(y->first))
                                    return;
                        }
                    }
                }
            }
        }
        
        
        /** \brief - To get the distance array at a particular instance **/
        DistanceArray<Graph>& getDistanceArray() {return dist;}
        
        /** \brief - To get the parent array at a particular instance **/
        ParentArray<Graph>& getParentArray() {return parent;}
        
        /** \brief - Hook for .... TODO **/
        void setp1(std::function<bool(const V&)> f){p1=f;}
        /** \brief - Hook for .... TODO**/
        void setp2(std::function<bool(const V&)> f){p2=f;}
        /** \brief - Hook for back edges **/
        void setp3(std::function<bool(const V&)> f){p3=f;}
        /** \brief - Hook for tree edges **/
        void setp4(std::function<bool(const V&,const V&)> f){p4=f;}
        
        void resetFringe(std::function<bool(V,V)> compare)//This can be used to implement heuristics
        {
            delete fringe; // TODO: more sophisticated memory management
            fringe = new Container<Graph>(compare);
        }
    protected:    
        
        Container<Graph>* fringe;
        DistanceArray<Graph> dist;
        ParentArray<Graph> parent;
        Graph& g;
        V source;
        std::function<bool(const V&)> p1, p2, p3;
        std::function<bool(const V&,const V&)> p4;
    };
    
    
    /** \brief - To implement Uniform Cost Search
     *
     * Uniform cost search is a tree search algorithm related to breadth-first search.
     * Whereas breadth-first search determines a path to the goal state that has the
     * least number of edges, uniform cost search determines a path to the goal state
     * that has the lowest weight.
     * Refernce Link  - <a href="http://math.wikia.com/wiki/Uniform_cost_search">UCS</a>
     **/
    template<typename G>
    using UniformCostSearch=Search<G,PriorityQueue>;
    /** \brief - To implement Depth First Search
     *
     * Depth-first search (DFS) is an algorithm for traversing or searching tree
     * or graph data structures. One starts at the root (selecting some arbitrary
     * node as the root in the case of a graph) and explores as far as possible
     * along each branch before backtracking.
     * Refernce Link  - <a href="http://en.wikipedia.org/wiki/Depth-first_search">DFS</a>
     **/
    template<typename G>
    using DepthFirstSearch=Search<G,Stack>;
    /** \brief - To implement Breadth First Search
     * Breadth-first search (BFS) is an algorithm for traversing or searching tree
     * or graph data structures. It starts at the tree root (or some arbitrary node
     * of a graph, sometimes referred to as a `search key'[1]) and explores the neighbor
     * nodes first, before moving to the next level neighbours.
     * Refernce Link  - <a href="http://en.wikipedia.org/wiki/Breadth-first_search">BFS</a>
     **/
    template<typename G>
    using BreadthFirstSearch=Search<G,Queue>;
    
    
}
#endif
