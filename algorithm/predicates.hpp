/**	\brief predicates.hpp - Header file that has collection of boolean functions 
/**      on a graph object. All these checks must evaluate to true or false.
/**      
/**      Note: Use std::bind on these predicates and a Graph object for these to be 
/**      applicable to STL algorithms.
/**      
 * **/
#ifndef GRAPH_ALGORITHM_PREDICATES_HPP
#define GRAPH_ALGORITHM_PREDICATES_HPP
#include "../graph.hpp"
# include "enumeration.hpp"
#include "search.hpp"
#include "collections.hpp"
#include<vector>
#include<algorithm>
namespace graph
{
    /**
     * \brief - Returns true if Graph::VertexType x is a vertex of Graph g,
     *  false otherwise
     * 
     * Graph g - First parameter, a graph object
     *   
     * Graph::VertexType x- Second parameter, the vertex
     * **/
    template<typename Graph>
    bool isVertex(Graph& g,typename Graph::VertexType x)
    {
        return g.find(x)!=g.end();
    }
    
    /**
     * \brief - Returns true if Graph::VertexType x and Graph::VertexType y
     * are adjacent in Graph g, false otherwise
     * 
     * Graph g - First parameter, a graph object
     *   
     * Graph::VertexType x- Second parameter, the first vertex
     * 
     * Graph::VertexType y- Third parameter, the second vertex
     * **/
     
    template<typename Graph>
    bool isAdjacent(Graph& g,typename Graph::VertexType x,typename Graph::VertexType y)
    {
        if(isVertex(g,x) && isVertex(g,y))
            return g.nfind(x,y)!=g.nend(x);
        return false;
    }
    
     /**
     * \brief - Returns true if Graph g is a subgraph of Graph h, false otherwise
     * 
     * Graph g - First parameter, a graph object
     *   
     * Graph h - Second parameter, a graph object
     * **/
     
    template<typename Graph>
    bool isSubgraph(Graph& g,Graph& h) //is 'g' subgraph of 'h'
    {
        if(h.order()<g.order())
            return false;
        for(auto i=g.begin();i!=g.end();++i)
            if(!(isVertex(h,i->first)))
                return false;
        for(auto i=g.begin();i!=g.end();++i)
            for(auto j=g.nbegin(i->first);j!=g.nend(i->first);++j)
                if(!(isAdjacent(h,i->first,j->first)))
                    return false;
        return true;
    }
    /**
     * \brief - Returns true if Graph g is a spanning subgraph of Graph h,
     * false otherwise
     * 
     * Graph g - First parameter, a graph object
     *   
     * Graph h - Second parameter, a graph object
     * **/
    
    template<typename Graph>
    bool isSpanningSubgraph(Graph& g,Graph& h) //is 'g' spanning_subgraph of 'h'
    {
        if(g.order()==h.order() && isSubgraph(g,h))
            return true;
        return false;
    }
    /**
     * \brief - Returns true if all vertices of Graph g can be traversed,
     * false otherwise
     *  
     * Graph g - Parameter, a graph object
     * **/
    template<typename Graph>
    bool isConnected(Graph& g)
    {
        BreadthFirstSearch<Graph> bfs(g,g.begin()->first);
        bfs();
        auto d=bfs.getDistanceArray();
        
        return d.size()==g.order();
    }
    /**
     * \brief - Returns true if Graph::VertexType y can be reached from 
     * Graph::VertexType x in Graph g, false otherwise
     * 
     * Graph g - First parameter, a graph object
     *   
     * Graph::VertexType x- Second parameter, the first vertex
     * 
     * Graph::VertexType y- Third parameter, the second vertex
     * **/
    template<typename Graph>
    bool isConnected(Graph& g,typename Graph::VertexType x,typename Graph::VertexType y)
    {
        HookedSearch<Graph,Queue> searchObject(g,x);
        bool connected=false;
        searchObject.m_p2=[&](const typename Graph::VertexType& v)
        {
            if(v==y)
            {
                connected=true;
                return false;
            }
            return true;
        };
        searchObject.execute();
        return connected;
    }
    
    /**
     * \brief - Returns true if Graph g1 is a component of Graph g2,
     *  false otherwise
     * 
     * Graph g1 - First parameter, a graph object
     *   
     * Graph g2 - Second parameter, a graph object
     * **/
    
    template<typename Graph>
    bool isComponent(Graph& g1,Graph& g2)  //is 'g1' component of 'g2' 
    {
        if(!(isConnected(g1)&&isSubgraph(g1,g2)))
            return false;
        BreadthFirstSearch<Graph> bfs(g2,g1.begin()->first);
        bfs();
        auto d=bfs.getDistanceArray();
        if(d.size()!=g1.order())
            return false;
        return true;
    }
    
    /**
     * \brief - Returns true if degree of all vertices in Graph g is equal,
     *  false otherwise
     * 
     * Graph g - Parameter, a graph object
     * **/
     
    template <typename Graph>
    bool isRegular(Graph &g)
    {
        int k=degree(g,g.begin()->first);
        
        for (auto x=g.begin();x!=g.end();++x)
        {
            if (g.isDirected())
            {
                if (inDegree(g,x->first)!=outDegree(g,x->first))
                    return false;
            }
            if(k!=degree(g,x->first))
                return false;
          
        }
        return true;
    }
    
    /** \brief - Returns true if degree of all vertices in Graph g is even and
     *  Graph g is connected, false otherwise
     * 
     * Graph g - Parameter, a graph object
     * **/
     
    template <typename Graph>
    bool isEulerian(Graph &g)
    {
        if (g.isDirected())
        {
            for (auto x=g.begin();x!=g.end();++x)
            {
                if (degree(g,x->first)==0)
                    return false;
                if (inDegree(g,x->first)!=outDegree(g,x->first))
                    return false;
            }
            return true;
        }
        if (isConnected(g))
        {
            for (auto x=g.begin();x!=g.end();++x)
            {
                int k=degree(g,x->first);
                if(k%2!=0)
                    return false;
            }
            return true;
        }
        else
            return false;
    }
    
    /** \brief - Returns true if degree of exactly two vertices in Graph g is even
     *  and Graph g is connected, false otherwise
     * 
     * Graph g - Parameter, a graph object
     * **/
     
    template <typename Graph>
    bool isSemiEulerian(Graph &g)
    {
        if (g.isDirected())
        {
            bool out = false;
            bool in = false;
            for (auto x=g.begin();x!=g.end();++x)
            {
                if (degree(g,x->first)==0)
                    return false;
                int id = inDegree(g,x->first);
                int od = outDegree(g,x->first);
                if (id==od)
                {
                    continue;
                }
                if (out == 1 + in)
                {
                    if(out)
                        return false;
                    else out = true;
                }
                else if (in == 1 + out)
                {
                    if(in)
                        return false;
                    else in = true;
                }
                else return false;
            }
            return true;
        }
        if (isConnected(g))
        {
            int count=0;
            for (auto x=g.begin();x!=g.end();++x)
            {
                int k=degree(g,x->first);
                if(k%2!=0)
                    count++;
            }
            if(count==2)
                return true;
            else
                return false;
        }
        else
            return false;
    }
    
    /** \brief - Returns true if atleast one edge is present between all
     *  combination of vertices (except self loops) in Graph g, false otherwise
     * 
     * Graph g - Parameter, a graph object
     * **/
    
    template <typename Graph>
    bool isComplete(Graph &g)
    {
        for (auto x=g.begin();x!=g.end();++x)
            for (auto y=g.begin();y!=g.end();++y)
            {
                if (x!=y && !(isAdjacent(g,x->first,y->first)))
                    return false;
                 if (g.isDirected() && !(isAdjacent(g,y->first,x->first)))
                        return false;
            }
        return true;
    }
    
    /**
     * \brief  - Returns true if edges present in Graph g are not present
     * in Graph h and vice versa (neglecting self loops), false otherwise
     * 
     * Graph g - First parameter, a graph object
     *   
     * Graph h - Second parameter, a graph object
     * **/
    
    template <typename Graph>
    bool isComplement(Graph &g, Graph &h)
    {
        for (auto x=g.begin();x!=g.end();++x)
            for (auto y=g.begin();y!=g.end();++y)
                if (x!=y)
                    if(isAdjacent(g,x->first,y->first) && isAdjacent(h,x->first,y->first))
                        return false;
                    
                    return true;
    }
    
    /** \brief - Returns true if there are no edges in Graph g, false otherwise
     * 
     * Graph g - Parameter, a graph object
     * **/
    
    template <typename Graph>
    bool isEdgeless(Graph &g)
    {
        for (auto x=g.begin();x!=g.end();++x)
            for (auto y=g.begin();y!=g.end();++y)
                if(isAdjacent(g,x->first,y->first))
                    return false;
                
                return true;

    }
    
    /** \brief - Returns true if there is atleast one path starting and ending
     * at the same vertex in Graph g, false otherwise
     * 
     * Graph g - Parameter, a graph object
     * **/
    
    template<typename Graph>
    bool isCyclic(Graph& g)
    {
        HookedSearch<Graph,Stack> searchObject(g,g.begin()->first);
        bool cyclic=false;
        searchObject.m_p3=[&](const typename Graph::VertexType& v)
        {
            cyclic=true;
            return false;
        };
        searchObject.execute();
        return cyclic;
    }
    
    /**
     * \brief - Returns true if Graph::VertexType x is at the centre of Graph g,
     *  false otherwise
     * 
     * Graph g - First parameter, a graph object
     *   
     * Graph::VertexType x- Second parameter, the vertex
     * **/
    
    template<typename Graph>
    bool isCentre(Graph& g,typename Graph::VertexType x)
    {
        auto s=Centre(g);
        return s.find(x)!=s.end();
    }
    
    /**
     * \brief - Returns true if Graph::VertexType x lies at the periphery of Graph g,
     *  false otherwise
     * 
     * Graph g - First parameter, a graph object
     *   
     * Graph::VertexType x- Second parameter, the vertex
     * **/
    
    template<typename Graph>
    bool isPeriphery(Graph& g,typename Graph::VertexType x)
    {
        auto s=Periphery(g);
        return s.find(x)!=s.end();
    }
    
    /** \brief - Returns true if there are no vertex in Graph g, false otherwise
     * 
     * Graph g - Parameter, a graph object
     * **/
    
    template<typename Graph>
    bool isEmpty(Graph& g) //is vertexless graph
    {
       return (g.begin()==g.end());
    }
    
    /** \brief - Returns true if number of edges in Graph g is less than or equal
     * to twice the number of vertices in graph g, false otherwise
     * 
     * Graph g - Parameter, a graph object
     * **/
    
    template<typename Graph>
    bool isSparse(Graph& g) 
    {
        int count=0;
        for (auto x=g.begin();x!=g.end();x++)
        for (auto y=g.begin();y!=g.end();y++)
            if(x!=y && isAdjacent(g,x->first,y->first))
                count++;
            if (g.isDirected())
                for (auto x=g.begin();x!=g.end();x++)
                    for (auto y=g.begin();y!=g.end();y++)
                        if(isAdjacent(g,y->first,x->first))
                            count++;
        int n=(g.isDirected()?4*g.order():2*g.order());
        if (count<=n)
            return true;
        return false;
    }
    
    /** \brief - Returns true if Graph g is a tree, false otherwise
     * 
     * Graph g - Parameter, a graph object
     * **/
        
    template<typename Graph>
    bool isTree(Graph& g) 
    {
        if(!isCyclic(g)&&isConnected(g))
            return true;
        return false;
    }
}
#endif
