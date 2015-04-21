#ifndef GRAPH_ALGORITHM_COLLECTIONS_HPP
#define GRAPH_ALGORITHM_COLLECTIONS_HPP
#include "../graph.hpp"
#include "../util/visitors.hpp"
#include "sssp.hpp"
#include "enumeration.hpp"
#include "predicates.hpp"
#include "search.hpp"
#include "apsp.hpp"
#include "../structures/attribute.hpp"
#include "../structures/parent.hpp"
#include "coloring.hpp"
#include<vector>
#include<map>
#include<set>
#include<tuple>
#include<algorithm>
#include<stdexcept>
#include<utility>
/**	\brief collection.hpp - Header file that has functions that returns sequences and lists of
 *  different aspects of a graph object
 * **/
namespace graph
{
    /**
     * \brief - Returns a list containing names of all the vertices in Graph g
     * 
     * @param Graph g - Parameter, a graph object
     *   
     * @returns vector<typename Graph::VertexType> v - vector to store the list
     * **/
     
    template<typename Graph>
    std::vector<typename Graph::VertexType> VertexList(Graph& g)
    {
        std::vector<typename Graph::VertexType> v;
        VisitVertices(g,[&v](typename Graph::VertexType x){v.push_back(x);}); // put auto after enabling c++11
        return v;
    }
    
    /**
     * \brief - Returns a list containing of adjacent vertices with edge weights
     * 
     * This function returns a list containing pairs of vertices which are connected by an edge.
     * The list also contains the edge weights for each edge.
     * 
     * @param Graph g - First parameter, a graph object
     * 
     * @param bool duplicate - Second parameter, to check for duplicate edges
     *   
     * @returns vector<std::tuple<typename Graph::VertexType,typename Graph::VertexType,typename Graph::EdgeType>> e - vector to store the list
     * **/
     
    template<typename Graph>
    std::vector
    <
        std::tuple
        <
            typename Graph::VertexType,
            typename Graph::VertexType,
            typename Graph::EdgeType
        >
    >
    EdgeList(Graph& g,bool duplicate=true)
    {
        std::vector<std::tuple<typename Graph::VertexType,typename Graph::VertexType,typename Graph::EdgeType>> e;
        for(auto i=g.begin();i!=g.end();++i)
            for(auto j=g.nbegin(i->first);j!=g.nend(i->first);++j)
                if(!g.isDirected()&& !duplicate)
                {
                    if(std::find(e.begin(),e.end(),std::make_tuple(j->first,i->first,j->second))==e.end())
                        e.push_back(std::make_tuple(i->first,j->first,j->second));
                }
                else
                    e.push_back(std::make_tuple(i->first,j->first,j->second));
        return e;
    }
    /**
     * 	\brief - A function to compare the edges between two vertices
     * **/
    
    template <typename Graph>
    bool sortComparison
    (
        std::tuple
        <   
            typename Graph::VertexType,
            typename Graph::VertexType,
            typename Graph::EdgeType
        > a,
        std::tuple
        <   
            typename Graph::VertexType,
            typename Graph::VertexType,
            typename Graph::EdgeType
        > b
    )
    {
        return (std::get<2>(a)<std::get<2>(b));
    }
    /**
     * \brief - eturns a list containing of adjacent vertices with edge weights
     * 
     * This function returns a list containing pairs of vertices which are connected by an edge.
     * The list also contains the edge weights for each edge. The list is sorted by edge weight
     * in ascending order.
     * 
     * 
     * @param Graph g - First Parameter, a graph object
     * 
     * @param bool duplicate - Second Parameter, to check for duplicate edges
     *   
     * @returns std::vector<std::tuple<typename Graph::VertexType,typename Graph::VertexType,typename Graph::EdgeType>> e - variable to store the sorted edge list
     * **/
    
    template <typename Graph>
    std::vector
    <
        std::tuple
        <
            typename Graph::VertexType,
            typename Graph::VertexType,
            typename Graph::EdgeType
        >
    >
    sortedEdgeList(Graph& g,bool duplicate=true)
    {
         std::vector<std::tuple<typename Graph::VertexType,typename Graph::VertexType,typename Graph::EdgeType>> e=EdgeList(g,duplicate);
         std::sort(e.begin(),e.end(),sortComparison<Graph>);
         return e;
    }
    
    /**
     * \brief - Returns a list containing all the vertices of Graph g
     * alongwith the total number of edges of each vertex
     * 
     * @param Graph g - Parameter, a graph object
     *   
     * @returns map<typename Graph::VertexType,int> m - variable to store the list
     * **/
     
    template<typename Graph>
    std::map<typename Graph::VertexType,int> DegreeMap(Graph& g)
    {
        std::map<typename Graph::VertexType,int> m;
        for(auto i=g.begin();i!=g.end();++i)
            m[i->first]=degree(g,i->first);
        return m;
    }
    
    /**
     * \brief - Returns a sequence of total number of edges of all vertices in Graph g in sorted
     * order
     * 
     * The list is sorted in ascending order.
     * 
     * @param Graph g - Parameter, a graph object
     *   
     * @returns vector<int> ds - variable to store the sequence
     * **/
     
    template<typename Graph>
    std::vector<int> DegreeSequence(Graph& g)
    {
        std::vector<int> ds;
        for(auto i=g.begin();i!=g.end();++i)
            ds.push_back(degree(g,i->first));
        std::sort(ds.begin(),ds.end());
        return ds;
    }
    
    /**
     * \brief - Returns a map of all vertices in Graph g with their corresponding eccentricities
     * 
     * Eccentricity of a vertex is the maximum distance that can be covered starting from that
     * vertex in a linear acyclic path.
     * 
     * @param Graph g - Parameter, a graph object
     *   
     * @returns map<typename Graph::VertexType,typename Graph::EdgeType> m - variable to store the mapping
     * **/
    
    template<typename Graph>
    std::map<typename Graph::VertexType,typename Graph::EdgeType> EcentricityList(Graph& g, bool check = true)
    {
        if (check == true)
            if(g.isDirected() || !isConnected(g))
                throw std::runtime_error("Not Possible : 'g'-> Undirected and Connected not met ...");
        std::map<typename Graph::VertexType,typename Graph::EdgeType> m;
        for(auto i=g.begin();i!=g.end();++i)
        {
            UniformCostSearch<Graph> ucs(g,i->first);
            ucs();
            auto d = ucs.getDistanceArray();
            auto max = d[g.begin()->first];
            for(auto j = g.begin();j != g.end(); ++j)
                if(d[j->first] > max)
                    max = d[j->first];
             m[i->first] = max;
        }
        return m;
    }
    
     /**
     * \brief - Returns a set of vertices constituting the centre in Graph g
     * 
     * Centre of a graph is the set of vertices with minimum eccentricity.
     * 
     * @param Graph g - Parameter, a graph object
     *   
     * @returns set<typename Graph::VertexType> s - variable to store the centres
     * **/
    
    template<typename Graph>
    std::set<typename Graph::VertexType> Centre(Graph& g)
    {
        std::set<typename Graph::VertexType> s;
        auto e=EcentricityList(g);
        auto min=e.begin()->second;
        for(auto i=e.begin();i!=e.end();++i)
                if(i->second<min)
                    min=i->second;
        for(auto i=e.begin();i!=e.end();++i)
            if(min==i->second)
                s.insert(i->first);
        return s;
    }
    
     /**
     * \brief - Returns a set of vertices constituting the periphery in Graph g
     * 
     * Periphery is a set of vertices with the maximum eccentricity.
     * 
     * @param Graph g - Parameter, a graph object
     *   
     * @returns set<typename Graph::VertexType> s - variable to store the peripheries
     * **/
   
    
    template<typename Graph>
    std::set<typename Graph::VertexType> Periphery(Graph& g)
    {
        std::set<typename Graph::VertexType> s;
        auto e=EcentricityList(g);
        auto max=e.begin()->second;
        for(auto i=e.begin();i!=e.end();++i)
                if(i->second>max)
                    max=i->second;
        for(auto i=e.begin();i!=e.end();++i)
            if(max==i->second)
                s.insert(i->first);
        return s;
    }
   
    /**
     * \brief - Returns adjacency matrix of Graph g
     * 
     * The matrix is a mapping between the pair of vertices and the edge between 
     * these two vertices
     * 
     * @param Graph g - Parameter, a graph object
     *   
     * @returns map<std::pair<typename Graph::VertexType,typename Graph::VertexType>,typename Graph::EdgeType> m - variable to store the adjacency matrix
     * **/
       
    template<typename Graph>
    std::map<std::pair<typename Graph::VertexType,typename Graph::VertexType>,typename Graph::EdgeType> AdjacencyMatrix(Graph& g)
    {
        std::map<std::pair<typename Graph::VertexType,typename Graph::VertexType>,typename Graph::EdgeType> m;
        for(auto i=g.begin();i!=g.end();++i)
            for(auto j=g.nbegin(i->first);j!=g.nend(i->first);++j)
                m[std::make_pair(i->first,j->first)]=j->second;
        return m;
    }
    
    /**
     * \brief - Returns a list containing all the vertices of Graph g having edges 
     * originating from Vertex x
     * 
     * @param Graph g - First parameter, a graph object
     * 
     * @param typename Graph::VertexType x - Second parameter, a vertex of Graph g
     *   
     * @returns map<typename Graph::VertexType> v - variable to store the list
     * **/
    
    template<typename Graph>
    std::vector<typename Graph::VertexType> OutVertexList(Graph& g,typename Graph::VertexType x)
    {
        std::vector<typename Graph::VertexType> v;
        for(auto i=g.nbegin(x);i!=g.nend(x);++i)
            v.push_back(i->first);
        
        return v;
    }
    
    /**
     * \brief - Returns a list containing all vertices of Graph g having edges
     * ending at Vertex x
     * 
     * @param Graph g - First Parameter, a graph object
     * 
     * @param typename Graph::VertexType x - Second parameter, a vertex of Graph g
     *   
     * @returns map<typename Graph::VertexType> v - variable to store the list
     * **/
    
    template<typename Graph>
    std::vector<typename Graph::VertexType> InVertexList(Graph& g,typename Graph::VertexType x)
    {
        if(!g.isDirected())
            return OutVertexList(g,x);
        else
        {
            std::vector<typename Graph::VertexType> v;
            for(auto i=g.begin();i!=g.end();++i)
            {
                auto it=g.nfind(i->first,x);
                if(it!=g.nend(i->first))
                    v.push_back(i->first);
            }
            return v;
        }           
    }
    
    /**
     * \brief - Returns a mapping of vertices and their corresponding colours
     * 
     * this employs a brute force approach. the vertex colouring is done using the minimum
     * number of colours possible.
     * 
     * @param Graph& g - Parameter, a graph object
     * 
     * @returns VertexAttribute<Graph, int> vattr - the mapping of vertices and their colours
     * **/
    template<typename Graph>
    VertexAttribute<Graph, int> minVertexColorAssignment(Graph& g)
    {
        auto state = minVertexColoring(g);
        VertexAttribute<Graph, int> vattr(state.getColorMap());
        return vattr;
    }
    /**
     * \brief - Returns a mapping of vertices and their corresponding colours
     * 
     * this employs someheuristics to reduce complexity. the vertex colouring is
     * not guaranteed to be done using the minimum number of colours possible everytime.
     * 
     * @param Graph& g - Parameter, a graph object
     * 
     * @returns VertexAttribute<Graph, int> vattr - the mapping of vertices and their colours
     * **/
    template<typename Graph>
    VertexAttribute<Graph, int> VertexColorAssignment(Graph& g)
    {
        auto state = WelshPowellColoring(g);
        VertexAttribute<Graph, int> vattr(state.getColorMap());
        return vattr;
    }
    /**
     * \brief - Returns an Eulerian Circuit of a graph
     * 
     * An Eulerian Circuit is a circuit that visits every edge of a graph exactly once.
     * This employs Hierholzer's algorithm.
     * 
     * @param Graph g - Parameter, a graph object
     * 
     * @returns std::vector<V> path - an Eulerian Circuit
     * **/
    template<typename Graph>
    std::vector<typename Graph::VertexType> EulerianCircuit(Graph g, bool isStartGiven=false, typename Graph::VertexType start=1)
    {
        if(!isEulerian(g))
            throw std::runtime_error("g is not eulerian ...");
        typedef typename Graph::VertexType V;
        std::vector<V> path;
        std::set<V> visited;
        std::map<V,std::vector<V>> unusedEdges;                             // unused edges FROM each vertex
        for(auto i=g.begin();i!=g.end();++i)
            for(auto j=g.nbegin(i->first);j!=g.nend(i->first);++j)
                unusedEdges[i->first].push_back(j->first);
        if(!isStartGiven)
            start = g.begin()->first;
        auto it = path.begin();
        
        while(1)
        {
            V v = start;
            visited.insert(v);
            if(path.empty())
                it = path.insert(it,v);
                
            do
            {
                for(auto w=g.nbegin(v);w!=g.nend(v);++w)                    // basic cycle find
                {
                    auto it1 = std::find(unusedEdges[v].begin(), unusedEdges[v].end(), w->first);
                    if( it1 != unusedEdges[v].end())
                    {
                        unusedEdges[v].erase(it1);
                        if(!g.isDirected())
                        {
                            auto it2 = std::find(unusedEdges[w->first].begin(), unusedEdges[w->first].end(), v);
                            unusedEdges[w->first].erase(it2);
                        }
                        visited.insert(w->first);
                        it = path.insert(it,w->first);
                        v = w->first;
                        break;
                    }
                }
            }while(v != start);
            
            bool flag = false;
            for(auto i=g.begin();i!=g.end();++i)                                               // check for existence of other cycles
                if(visited.find(i->first)!=visited.end() && !unusedEdges[i->first].empty())
                {
                    start = i->first;
                    it = std::find(path.begin(), path.end(), i->first);
                    flag = true;
                }
            
            if(flag == false)
                break;
        }
        
        return path;
    }
    
    /**
     * \brief - Returns an Eulerian trail of a graph
     * 
     * An Eulerian Trail is a trail that visits every edge of a graph exactly once.
     * This employs an augemnted version of Hierholzer's algorithm.
     * 
     * @param Graph g - Parameter, a graph object
     * 
     * @returns std::vector<V> path - an Eulerian Trail
     * **/
    template<typename Graph>
    std::vector<typename Graph::VertexType> EulerianTrail(Graph g)
    {
        if(isEulerian(g))
        {
            auto path = EulerianCircuit(g);
            path.pop_back();
            return path;
        }
        if(!isSemiEulerian(g))
            throw std::runtime_error("g is not semi-eulerian ...");
        std::vector<typename Graph::VertexType> oddVertices;
        for(auto i=g.begin();i!=g.end();++i)
            if(degree(g,i->first)%2!=0)
                oddVertices.push_back(i->first);
        g.insertEdge(oddVertices[0],oddVertices[1],1);
        auto path = EulerianCircuit(g,oddVertices[0]);
        path.pop_back();
        return path;
    }
    
    /**
     * \brief - Returns a Hamiltonian Path of a graph
     * 
     * A Hamiltonian Path is a path that visits every vertex of a graph exactly once.
     * 
     * @param Graph g - Parameter, a graph object
     * 
     * @returns std::vector<V> path - a Hamiltonian Path
     * **/
    template<typename Graph>
    std::vector<typename Graph::VertexType> HamiltonianPath(Graph g)
    {
        auto vlist = VertexList(g);
        std::sort(vlist.begin(),vlist.end());
        
        do
        {
            bool flag = true;
            auto v = vlist[0];
            for(int i=1;i<vlist.size();++i)
            {
                if(!isAdjacent(g,v,vlist[i]))
                {
                    flag = false;
                    break;
                }
                v = vlist[i];
            }
            if(flag == true)
                return vlist;
        }while(std::next_permutation(vlist.begin(),vlist.end()));
        
        throw std::runtime_error("g is not semi-hamiltonian ...");
    }
    
    /**
     * \brief - Returns a Hamiltonian Cycle of a graph
     * 
     * A Hamiltonian Cycle is a cycle that visits every vertex of a graph exactly once.
     * 
     * @param Graph g - Parameter, a graph object
     * 
     * @returns std::vector<V> path - a Hamiltonian Cycle
     * **/
    template<typename Graph>
    std::vector<typename Graph::VertexType> HamiltonianCycle(Graph g)
    {
        auto vlist = VertexList(g);
        std::sort(vlist.begin(),vlist.end());
        
        do
        {
            bool flag = true;
            auto v = vlist[0];
            for(int i=1;i<vlist.size();++i)
            {
                if(!isAdjacent(g,v,vlist[i]))
                {
                    flag = false;
                    break;
                }
                v = vlist[i];
            }
            if(flag == true && isAdjacent(g,vlist.front(),vlist.back()))
            {
                vlist.push_back(vlist.front());
                return vlist;
            }
        }while(std::next_permutation(vlist.begin(),vlist.end()));
        
        throw std::runtime_error("g is not hamiltonian ...");
    }
    
    /**
     * \brief - Returns a bipartition of Graph g, if exists, throws a std::runtime_error otherwise.
     * 
     * @param Graph& g - Parameter, a graph object
     *   
     * @returns std::pair<std::vector<typename Graph::VertexType>, std::vector<typename Graph::VertexType>> result - 
     * variable to store the pair of vectors of vertices where each vector is partition.
     * **/
    template<typename Graph>
    std::pair<std::vector<typename Graph::VertexType>, std::vector<typename Graph::VertexType>> Bipartition(Graph& g)
    {
        std::pair<std::vector<typename Graph::VertexType>, std::vector<typename Graph::VertexType>> result;
        BreadthFirstSearch<Graph> bfs(g,g.begin()->first);
        bool flag = true;
        std::map<typename Graph::VertexType, int> label;
        label[g.begin()->first] = 1;
        bfs.setp4([&label](const typename Graph::VertexType& x, const typename Graph::VertexType& y)
        {
            label[y] = -label[x];
            return true;
        });
        bfs.setp3([&flag,&label](const typename Graph::VertexType& x, const typename Graph::VertexType& y)
        {
            if(label[x] == label[y])
            {
                flag = false;
                return false;
            }
            return true;
        });
        bfs();
        if(flag == false)
            throw std::runtime_error("Graph not bipartite");
        else
        {
            for(auto i=g.begin();i!=g.end();++i)
                if(label[i->first] == 1)
                    result.first.push_back(i->first);
                else
                    result.second.push_back(i->first);
        }
        return result;
    }
    
    template<typename Graph>
    std::map<typename Graph::VertexType, std::vector<typename Graph::VertexType>> DijkstraPath(Graph g, typename Graph::VertexType source)
    {
        std::map<typename Graph::VertexType, std::vector<typename Graph::VertexType>> result;
        auto state = graph::Djikstra<Graph>(g,source);
        auto parent = state.getParentArray();
        for(auto i=g.begin();i!=g.end();++i)
            result[i->first] = parent.getPath(i->first);
        return result;
    }
   
    template<typename Graph>
    std::map<typename Graph::VertexType, std::vector<typename Graph::VertexType>> BellmanFordPath(Graph g, typename Graph::VertexType source)
    {
        std::map<typename Graph::VertexType, std::vector<typename Graph::VertexType>> result;
        auto state = graph::BellmanFord<Graph>(g,source);
        auto parent = state.getParentArray();
        for(auto i=g.begin();i!=g.end();++i)
            result[i->first] = parent.getPath(i->first);
        return result;
    }
   
    template<typename Graph>
    typename APSPState<Graph>::PM FloydRoyWarshallPath(Graph g)
    {
        auto state = FloydRoyWarshall<Graph>(g);
        return state.getPathArray();
    }
   
    template<typename Graph>
    DistanceArray<Graph> DijkstraDistance(Graph g, typename Graph::VertexType source)
    {
        return Djikstra<Graph>(g,source).getDistanceArray();
    }
   
    template<typename Graph>
    DistanceArray<Graph> BellmanFordDistance(Graph g, typename Graph::VertexType source)
    {
        return BellmanFord<Graph>(g,source).getDistanceArray();
    }
   
    template<typename Graph>
    typename APSPState<Graph>::AM FloydRoyWarshallDistance(Graph g)
    {
        return FloydRoyWarshall<Graph>(g).getDistanceArray();
    }
}
#endif
