#ifndef GRAPH_STRUCTURES_DISJOINTSET_HPP
#define GRAPH_STRUCTURES_DISJOINTSET_HPP
#include "parent.hpp"
#include <map>
/**
 * \brief disjointset.hpp -Header that contains disjointset structure
 * **/
namespace graph
{
	/** 
	 * \brief - Class to implement disjoint set datastructure using
	 * union by rank.
	 * 
	 * It is a data structure that keeps track of a set of elements 
	 * partitioned into a number of disjoint (nonoverlapping) subsets.
	 * **/
    template<typename Graph>
    class DisjointSet
    {
    public:
        typedef typename Graph::VertexType V; ///<Vertex
        /**
         * \brief - cosntructor to initialize parent array and rank array for a graph
         * 
         * @param Graph g - Parameter, a graph datastructure
         * **/
        DisjointSet(Graph g)
        {
            for(auto i=g.begin();i!=g.end();++i)
            {
                parent[i->first] = i->first;
                rank[i->first] = 0;
            }
        }
        /**
         * \brief - fucntion to find the root of a vertex
         * 
         * @param V v - Parameter, a vertex
         * **/
        V findRoot(V v)
        {
            if(v != parent[v])
                return findRoot(parent[v]);
            else
                return v;
        }
        /**
         * \brief - function to find the union of roots od two vertices
         * 
         * if the root of two vertices are the same then the union of roots of these two vertices
         * would e the root of either. if the roots of two vertices are no the same then the root
         * with higher rank is made the parent of the other root.
         * 
         * @param V x - First Parameter, a vertex
         * 
         * @param V y - Second Parameter, a vertex
         * **/
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
