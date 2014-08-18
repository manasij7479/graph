/** \brief - Contains execution of different searching algorithms with and without using Callback Funtions
 * **/

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

namespace graph
{
    template
    <
        typename Graph,
        template <typename> class Container,
        template 
        <
            typename,
            template <typename> class
        > 
        class Child     //Bad CRTP design, could possibly be improved with var-templates
    >
    class Search
    {
    public:
        typedef typename Graph::VertexType VertexType;
        typedef typename Graph::EdgeType EdgeType;
        typedef typename edge_traits<EdgeType>::DistanceType DistanceType;
        typedef Child<Graph,Container> Derived;
        
        Search(Graph& g_,const VertexType& s, std::function<bool(VertexType,VertexType)> compare)
            :fringe(compare),g(g_),source(s) {}
        virtual void operator()()
        {
            execute();
        }
        
        //hooks
        /**\brief - Callback Function to return on getting the source vertex from container**/
        virtual bool p1(const VertexType& v){return true;};
        /**\brief - Callback Function to return on getting the destination vertex
         * before visiting all vertices of graph **/
        virtual bool p2(const VertexType& v){return true;};
        /**\brief - Callback Function o return on getting back edge **/
        virtual bool p3(const VertexType& v){return true;};
        
        /*DistanceType distanceTo(const VertexType& v)
        {
            return dist[v];
        }

        VertexType parentOf(const VertexType& v){return parent[v];}*/
        
        /** \brief - To get the distance array at a particular instance **/
        DistanceArray<Graph>& getDistanceArray() {return dist;}
        /** \brief - To get the parent array at a particular instance **/
        ParentArray<Graph>& getParentArray() {return parent;}
    /**
     * \brief - The basic framework to implement any of the three searches, UCS< DFS and BFS
     * with or without using hooks.
     * 
     * Container<Graph> fringe - can be used as a stack or queue or priority queue in this 
     * context
     * **/    
    protected:
        void execute()
        {
            dist[source]=DistanceType(0);
            parent[source]=source;
            fringe.put(source);
            if(!static_cast<Derived*>(this)->p1(source))
                return;
            while(!fringe.empty())
            {
                VertexType v=fringe.get();
                if(!static_cast<Derived*>(this)->p2(v))
                    return;
                for(auto y=g.nbegin(v);y!=g.nend(v);++y)
                {
                    
                    if(dist.isUnknown(y->first))
                    {
                        dist.set(y->first,dist[v]+y->second);
                        fringe.put(y->first);
                        parent[y->first]=v;
                    }
                    else
                    {
                        //back edge
                        if(g.isDirected())
                        {
                            if(!static_cast<Derived*>(this)->p3(y->first))
                                return;
                        }
                        else
                        {
                            if(parent[v]!=y->first)
                                if(!static_cast<Derived*>(this)->p3(y->first))
                                    return;
                        }
                    }
                }
            } 
        }
        Container<Graph> fringe;
        DistanceArray<Graph> dist;
        ParentArray<Graph> parent;
        Graph& g;
        VertexType source;
    };
    
    /** \brief - To implement any search operation without the use of any hooks**/
    template
    <
        typename Graph,
        template <typename> class Container
    >
    class DefaultSearch : public Search<Graph,Container,DefaultSearch>
    {
    public:
        typedef typename Graph::VertexType V;
        typedef Search<Graph,Container,DefaultSearch> Base;
        DefaultSearch(Graph& g,const typename Graph::VertexType& s)
            :Search<Graph,Container,DefaultSearch>(g,s,[&](V x,V y){return this->dist[x] < this->dist[y];})
        {
            Search<Graph,Container,DefaultSearch>::execute();
        }
    };
    
    /** \brief - To implement any search operation usin hooks **/
    template
    <
        typename Graph,
        template <typename> class Container
    >
    class HookedSearch : public Search<Graph,Container,HookedSearch>
    {
    public:
        typedef typename Graph::VertexType V;
        typedef Search<Graph,Container,DefaultSearch> Base;
        /** \brief - All of the hooks, namely p1, p2 and p3, are set to true as their default values **/
        HookedSearch(Graph& g,const V& s)
            :Search<Graph,Container,HookedSearch>(g,s,[&](V x,V y){return this->dist[x] < this->dist[y];})
        {
            m_p1=m_p2=m_p3=
            [](const V&)
            {
                return true;
            };
        }
        
        void execute()
        {
            Search<Graph,Container,HookedSearch>::execute();
        }
        bool p1(const V& v)
        {
            return m_p1(v);
        }
        bool p2(const V& v)
        {
            return m_p2(v);
        }
        bool p3(const V& v)
        {
            return m_p3(v);
        }
        std::function<bool(const V& v)> m_p1,m_p2,m_p3;
    };
    /** \brief - To implement Uniform Cost Search**/
    template<typename G>
    using UniformCostSearch=DefaultSearch<G,PriorityQueue>;
    /** \brief - To implement Depth First Search**/
    template<typename G>
    using DepthFirstSearch=DefaultSearch<G,Stack>;
    /** \brief - To implement Breadth First Search**/
    template<typename G>
    using BreadthFirstSearch=DefaultSearch<G,Queue>;
    
    
}
#endif
