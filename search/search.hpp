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
        VertexType parentOf(const VertexType& v){return parent[v];}
    protected:
        void execute()
        {
            dist[source]=DistanceType(0);
            parent[source]=source;
            fringe.put(source);
            if(!dynamic_cast<Derived*>(this)->p1(source))
                return;
            while(!fringe.empty())
            {
                VertexType v=fringe.get();
                if(!dynamic_cast<Derived*>(this)->p2(v))
                    return;
                for(auto y=g.nbegin(v);y!=g.nend(v);++y)
                {
                    auto it = dist.find(y->first);
                    if(it==dist.end())
                    {
                        dist[y->first]=dist[v]+y->second;
                        fringe.put(y->first);
                        parent[y->first]=v;
                    }
                    else
                    {
                        //back edge
                        if(g.isDirected())
                        {
                            if(!dynamic_cast<Derived*>(this)->p3(y->first))
                                return;
                        }
                        else
                        {
                            if(parent[v]!=y->first)
                                if(!dynamic_cast<Derived*>(this)->p3(y->first))
                                    return;
                        }
                    }
                }
            } 
        }
        Container<Graph> fringe;
        std::map<VertexType,DistanceType> dist;
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
        DefaultSearch(Graph& g,const typename Graph::VertexType& s)
            :Search<Graph,Container,DefaultSearch>(g,s)
        {
            Search<Graph,Container,DefaultSearch>::execute();
        }
    };
}
#endif