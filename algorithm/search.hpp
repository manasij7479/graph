#ifndef GRAPH_SEARCH_HPP
#define GRAPH_SEARCH_HPP

#include "../graph.hpp"
#include "../implementation/edge_traits.hpp"
#include "../structures/stack.hpp"
#include "../structures/queue.hpp"

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
        
        Search(Graph& g_,const VertexType& s)
            :fringe(dist),g(g_),source(s) {}
        virtual void operator()()
        {
            execute();
        }
        
        //hooks
        virtual bool p1(const VertexType& v){return true;};
        virtual bool p2(const VertexType& v){return true;};
        virtual bool p3(const VertexType& v){return true;};
        
        /*DistanceType distanceTo(const VertexType& v)
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
        VertexType parentOf(const VertexType& v){return parent[v];}*/
        
        DistanceArray<Graph>& getDistArray() {return dist;}
        std::map<VertexType,VertexType>& getParentArray() {return parent;}
        
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
        std::map<VertexType,VertexType> parent;
        Graph& g;
        VertexType source;
    };
    
    
    template
    <
        typename Graph,
        template <typename> class Container
    >
    class DefaultSearch : public Search<Graph,Container,DefaultSearch>
    {
    public:
        typedef typename Graph::VertexType V;;
        DefaultSearch(Graph& g,const typename Graph::VertexType& s)
            :Search<Graph,Container,DefaultSearch>(g,s)
        {
            Search<Graph,Container,DefaultSearch>::execute();
        }
    };
    
    template
    <
        typename Graph,
        template <typename> class Container
    >
    class HookedSearch : public Search<Graph,Container,HookedSearch>
    {
    public:
        typedef typename Graph::VertexType V;
        HookedSearch(Graph& g,const V& s)
            :Search<Graph,Container,HookedSearch>(g,s)
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
    
    template<typename G>
    using UniformCostSearch=Search<G,PriorityQueue,DefaultSearch>;
    
    template<typename G>
    using DepthFirstSearch=Search<G,Stack,DefaultSearch>;
    
    template<typename G>
    using BreadthFirstSearch=Search<G,Queue,DefaultSearch>;
    
    
}
#endif